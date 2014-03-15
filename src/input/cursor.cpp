#include <pspctrl.h>
#include <malloc.h>
#include "../framework.h"

Cursor::Cursor()
{
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	cursor = new CursorInfo();
	cursor->X = 480/2;
	cursor->Y = 280/2;
	Core::Cfg->GetIntValue("cursorspeed", cursor->CursorSpeed);
	cursor->Display = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_cursor").c_str());
	Core::Dbg->Log(Init, "Cursor Loaded...");
}

Cursor::~Cursor()
{
	Core::Gui->FreeImage(cursor->Display);
	delete(cursor);
}

void Cursor::Handle(SceCtrlData* pad)
{
	Core::Ctrl->PreviousAnalogX = cursor->X;
	Core::Ctrl->PreviousAnalogY = cursor->Y;
	
	bool change = false;
	// Update position
	if (pad->Lx > 145){ cursor->X += (pad->Lx - 145) / cursor->CursorSpeed; change = true;}
	if (pad->Lx < 93) { cursor->X -= (93 - pad->Lx) / cursor->CursorSpeed; change = true;}
	if (pad->Ly > 160){ cursor->Y += (pad->Ly - 160) / cursor->CursorSpeed; change = true;}
	if (pad->Ly < 100){ cursor->Y -= (100 - pad->Ly) / cursor->CursorSpeed; change = true;}
	if (!change)
	{
		Core::Gui->BlitAlphaImageToScreen(0, 0, cursor->Display->Width, cursor->Display->Height, cursor->Display, cursor->X, cursor->Y);
		return;
	}	
	// Check if cursor is still on the screen
	if (cursor->X < 0) cursor->X=0;
	if (cursor->X > 480) cursor->X = 480;
	if (cursor->Y < 0) cursor->Y=0;
	if (cursor->Y > 272) cursor->Y = 272;
	
	Core::Gui->BlitAlphaImageToScreen(0, 0, cursor->Display->Width, cursor->Display->Height, cursor->Display, cursor->X, cursor->Y);

	Core::Ctrl->AnalogX = cursor->X;
	Core::Ctrl->AnalogY = cursor->Y;
}
