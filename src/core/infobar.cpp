#include "../framework.h"
#include <psprtc.h>

InfoBar::InfoBar()
{
	_bar = new Image(SCREEN_WIDTH, 11);
	Core::Gui->ClearImage(0xFF2E3F45, _bar);

	// Render title
	Core::Fonts->PrintImage("Tactical Language Mobile 0.1", 160, 1, _bar, 0xFFFFFFFF, 0, 1);
	Core::Fonts->PrintImage("Previous", 1, 1, _bar, 0xFFFFFFFF, 0, 1);
	Core::Fonts->PrintImage("Next", 450, 1, _bar, 0xFFFFFFFF, 0, 1);

	/*/ Render time
	pspTime* _timed = (pspTime*) malloc(sizeof(pspTime));
	sceRtcGetCurrentClockLocalTime(_timed);
	char buf[20];
	sprintf(buf, "%02d:%02d",_timed->hour,_timed->minutes);
	Core::Fonts->PrintImage(buf, 350, 1, _bar, 0xFFFFFFFF, 0, 0);*/
}

InfoBar::~InfoBar()
{
	
}

void InfoBar::Render()
{
	Core::Gui->BlitImageToScreen(0, 0, _bar->Width, _bar->Height, _bar, 0, 0);
}
