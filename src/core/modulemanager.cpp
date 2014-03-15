#include <psptypes.h>
#include <pspumd.h>
#include <pspkernel.h>
#include <stdio.h>
using namespace std;

#include "../framework.h"

ModuleManager::ModuleManager()
{
	Core::Dbg->Log(Init, "Module Manager loaded...");
}

int ModuleManager::LoadStartModule(string path, string arg)
{
    	u32 loadResult;
    	u32 startResult;
    	int status;

    	loadResult = sceKernelLoadModule(path.c_str(), 0, NULL);
	if (loadResult & 0x80000000)
	{
		Core::Dbg->Log(Error, "Can't find module: " + path);
		return -1;
	}
	else
	{
		Core::Dbg->Log(Text, "Found module...");
		if (arg != "")
		{
			char arg_c[strlen(arg.c_str()) + 1];
			strcpy(arg_c, arg.c_str());
			Core::Dbg->Log(Text, "Starting module:");
			Core::Dbg->Log(Text, arg_c);
			startResult =sceKernelStartModule(loadResult, sizeof(arg_c), arg_c, &status, NULL);
		}
		else
			startResult =sceKernelStartModule(loadResult, 0, NULL, &status, NULL);
	}
	if (loadResult != startResult)
	{
		Core::Dbg->Log(Error, "Can't load module: " + path);
		return -2;
	}
	return 0;
}

void ModuleManager::LoadStartUMD()
{
	int res = sceUmdCheckMedium(0);
	if(res != 0)
	{
		LoadStartModule("ms0:/pspfw/kernmod.prx", "");
		sceKernelExitDeleteThread(0);
	}
	else
		Core::Dbg->Log(Warning, "No UMD found");
}

void ModuleManager::Reboot()
{
	LoadStartELF("reboot");
}

void ModuleManager::LoadStartELF(string path)
{
	LoadStartModule("ms0:/pspfw/kernmod.prx", path);
}
