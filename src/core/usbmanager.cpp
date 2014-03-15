#include <psptypes.h>
#include <pspusb.h>
#include <pspusbstor.h>

#include "../framework.h"

USBManager::USBManager()
{
	Core::Dbg->Log(Init, "USB Library loaded...");
}

void USBManager::ToggleUSB()
{
	ToggleUSB(0);
}

void USBManager::ToggleUSB(int silent)
{
	int state = sceUsbGetState();
	if (state & PSP_USB_ACTIVATED)
	{
		sceUsbDeactivate(0x1c8);
		Core::Dbg->Log(Text, "USB disabled");
	}
	else
	{
		sceUsbActivate(0x1c8);
			Core::Dbg->Log(Text, "USB Enabled");
	}
}

bool USBManager::IsEnabled()
{
	int state = sceUsbGetState();
	if (state & PSP_USB_ACTIVATED)
		return true;
	else
		return false;
}
