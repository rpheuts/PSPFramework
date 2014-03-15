#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <string.h>
#include <pspusb.h>
#include <pspusbstor.h>
#include "loadutil.h"

PSP_MODULE_INFO("Artilery", 0x1000, 1, 1);
// Define the main thread's attribute value (optional)
PSP_MAIN_THREAD_ATTR(0);

// Define printf, just to make typing easier
#define printf	pspDebugScreenPrintf

// Define the modules to be started
#define MODULE_COUNT 1
char *shellModules[MODULE_COUNT] = {"ms0:/pspfw/core.prx"};
#define KERN_MODULE_COUNT 5
char *kernModules[KERN_MODULE_COUNT] = {"flash0:/kd/semawm.prx", "flash0:/kd/usbstor.prx", "flash0:/kd/usbstormgr.prx", "flash0:/kd/usbstorms.prx", "flash0:/kd/usbstorboot.prx"};

// Exit callback
int exit_callback(int arg1, int arg2, void *arg)
{
	sceKernelExitGame();
	return 0;
}

// Callback thread
void CallbackThread(void *arg)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", (void*) CallbackThread, 0x11, 0xFA0, 0xa0000000, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

SceUID load_module(const char *path, int flags, int type)
{
	SceKernelLMOption option;
	SceUID mpid;

	/* If the type is 0, then load the module in the kernel partition, otherwise load it
	   in the user partition. */
	if (type == 0) {
		mpid = 1;
	} else {
		mpid = 2;
	}

	memset(&option, 0, sizeof(option));
	option.size = sizeof(option);
	option.mpidtext = mpid;
	option.mpiddata = mpid;
	option.position = 0;
	option.access = 1;

	return sceKernelLoadModule(path, flags, type > 0 ? &option : NULL);
}

int LoadStartModule(char *path)
{
    u32 loadResult;
    u32 startResult;
    int status;

    loadResult = sceKernelLoadModule(path, 0, NULL);
    if (loadResult & 0x80000000)
	return -1;
    else
	startResult =
	    sceKernelStartModule(loadResult, 0, NULL, &status, NULL);

    if (loadResult != startResult)
	return -2;

    return 0;
}

// call from KERNEL thread
int loadNetDrivers(SceModuleInfo* modInfoPtr)
{
    // libraries load where they want, patch workaround needed
    LoadAndStartAndPatch(modInfoPtr, "flash0:/kd/ifhandle.prx"); // kernel
    LoadAndStartAndPatch(modInfoPtr, "flash0:/kd/pspnet.prx");
    LoadAndStartAndPatch(modInfoPtr, "flash0:/kd/pspnet_inet.prx");
    LoadAndStartAndPatch(modInfoPtr, "flash0:/kd/pspnet_apctl.prx");
    LoadAndStartAndPatch(modInfoPtr, "flash0:/kd/pspnet_resolver.prx");
    FlushCaches();
    //REVIEW: add error checks
    return 0;
}

void init_modules()
{
	SceUID modid;
	SceModule *mod;
	int i = 0;
	int ret;
	int fd;
	
	printf("Loading USB drivers...\n");
	for (i=0; i<KERN_MODULE_COUNT; i++)
	{
		LoadStartModule(kernModules[i]);
	}

	printf("Loading Core modules...\n");
	for (i=0; i<MODULE_COUNT; i++)
	{
		modid = load_module(shellModules[i], 0, 1);
		mod = sceKernelFindModuleByUID(modid);
		if(mod != NULL)
		{
			// Start the module
			ret = sceKernelStartModule(modid, 0, NULL, &fd, NULL);
		}
		else
			printf("Failed loading: %s\n", shellModules[i]);
	}
	printf("Loading WiFi modules...\n");
	loadNetDrivers(&module_info);
}

void init_USB()
{
	int retVal;
	//setup USB drivers
	retVal = sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0);
	
	if (retVal != 0) 
	{
		printf("Error starting USB Bus driver (0x%08X)\n", retVal);
		sceKernelSleepThread();
	}
	
	retVal = sceUsbStart(PSP_USBSTOR_DRIVERNAME, 0, 0);
	if (retVal != 0) 
	{
		printf("Error starting USB Mass Storage driver (0x%08X)\n", retVal);
		sceKernelSleepThread();
	}
	
	retVal = sceUsbstorBootSetCapacity(0x800000);
	if (retVal != 0) 
	{
		printf("Error setting capacity with USB Mass Storage driver (0x%08X)\n", retVal);
		sceKernelSleepThread();
	}
	retVal = 0;
}

__attribute__ ((constructor))
void loaderInit()
{
	pspKernelSetKernelPC();
	pspSdkInstallNoDeviceCheckPatch();
}

int main(int argc, char** argv)
{
	// Set debug screen
	pspDebugScreenInit();
	pspDebugScreenClear();
	printf("PSP Framework bootloader\n");
	printf("--------------------------------------------\n\n");
	
	// Install error handlers
	pspDebugInstallErrorHandler(NULL);
	pspDebugInstallStdoutHandler(pspDebugScreenPrintData);
	pspSdkInstallNoPlainModuleCheckPatch();
	SetupCallbacks();
	
	// Setup environment
	printf("Start loading modules:\n");
	init_modules();
	init_USB();

	// End this thread
	sceKernelExitDeleteThread(0);
	return 0;
}
