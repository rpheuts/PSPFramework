#include "../framework.h"
#include "techdemo.h"

#define WINDOW_WIDTH 468
#define WINDOW_HEIGHT 252

TechDemo::TechDemo() : WindowApp(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	_over = 0;
	_playing = 0;
	_xml = 0;
	_posX = 10;
	_posY = 2;

	Core::Gui->ClearImage(0xAA2E3F45, Screen);
	_interface = new MSBInterfaceManager(this, 0xAA2E3F45);
	MSBParser* pd = new MSBParser();
	_lesson = pd->Parse("ms0:/pspfw/xml/demo.xml");
	_curPage = _lesson->Pages.begin();
	_update = 1;
	_test = Core::Gui->LoadPNG("ms0:/pspfw/wallpapers/psp_pashto.png");
}

TechDemo::~TechDemo()
{
	// Clean up
}

void TechDemo::HandleController(int mouseX, int mouseY, int btn)
{
	if (btn == PSP_CTRL_UP)
		_interface->Scroll(0, -7);
	if (btn == PSP_CTRL_DOWN)
		_interface->Scroll(0, 7);
	if (btn == PSP_CTRL_SQUARE && Core::Ctrl->IsLastInputPressed == 0)
	{
		PlayBackMP3::Init(0);
		PlayBackMP3::Load("ms0:/pspfw/audio/Salar0000000144.mp3");
		PlayBackMP3::Play();
	}
	if (btn == PSP_CTRL_RTRIGGER && Core::Ctrl->IsLastInputPressed == 0)
	{
		_curPage++;
		if (_curPage == _lesson->Pages.end())
			_curPage = _lesson->Pages.begin();
		_update = 1;
	}
	if (btn == PSP_CTRL_LTRIGGER && Core::Ctrl->IsLastInputPressed == 0)
	{
		if (_curPage == _lesson->Pages.begin())
			_curPage = _lesson->Pages.end();
		_curPage--;
		_update = 1;
	}
	_interface->HandleController(mouseX, mouseY, btn);
}

void TechDemo::HandleInputEvent(string EventID, string arg)
{
	if (EventID.compare("audio") == 0 && Core::Ctrl->IsLastInputPressed == 0)
	{
		string path = "ms0:/pspfw/audio/" + arg;

		PlayBackMP3::Init(0);
		PlayBackMP3::Load(path.c_str());
		PlayBackMP3::Play();
	}
}

void TechDemo::Destroy()
{
	// Prepare for window close
}

void TechDemo::Render()
{
	if (_update == 1)
	{
		Core::Gui->ClearImage(0xAA2E3F45, Screen);
		_interface->Clear();

		MSBPage* page = (MSBPage*)*_curPage;
		if (page->Category.compare("Pronunciation") == 0)
			RenderPronunciation(page);
		if (page->Category.compare("PassiveDialog") == 0)
			RenderPassiveDialogPage(page);
		if (page->Category.compare("Info") == 0)
			RenderInfoPage(page);

		_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);
		_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);
		_update = 0;
	}
}

void TechDemo::RenderPassiveDialogPage(MSBPage* page)
{
	MSBPassiveDialogPage* pdpage = (MSBPassiveDialogPage*)page;
	// Interface code
	_interface->AddText(pdpage->Title, 0xFFFFFFFF, 0, 1, 0);
	//_interface->AddText("Skills:", 0xFFFFFFFF, 0, 0, 0);

	/*list<Skill*>::iterator its;
	for( its = pdpage->Skills.begin(); its != pdpage->Skills.end(); its++ )
		_interface->AddText(((Skill*)*its)->Name, 0xFFFF0000, 0, 2, 10);*/
	_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);

	_interface->AddText("Dialog:", 0xFFFFFFFF, 0, 0, 0);
	list<Sentence*>::iterator it;
	for( it = pdpage->Sentences.begin(); it != pdpage->Sentences.end(); it++ )
	{
		_interface->AddText(((Sentence*)*it)->Speaker, 0xFF00FF00, 0, 2, 10);
		_interface->AddText(((Sentence*)*it)->Foreign, 0xFFFFFFFF, 0, 0, 20, 0);
		_interface->AddText(((Sentence*)*it)->English, 0xFFFFBBBB, 0, 0, 200);
		_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);
	} 
}

void TechDemo::RenderPronunciation(MSBPage* page)
{
	MSBPronunciationPage* pdpage = (MSBPronunciationPage*)page;

	// Interface code
	_interface->AddText(pdpage->Title, 0xFFFFFFFF, 0, 1, 0);
	//_interface->AddText("Skills:", 0xFFFFFFFF, 0, 0, 0);

	/*list<Skill*>::iterator its;
	for( its = pdpage->Skills.begin(); its != pdpage->Skills.end(); its++ )
		_interface->AddText(((Skill*)*its)->Name, 0xFFFF0000, 0, 2, 10);*/
	_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);

	list<Utterance*>::iterator it;
	for( it = pdpage->Utterances.begin(); it != pdpage->Utterances.end(); it++ )
	{
		_interface->AddButton("", "audio", ((Utterance*)*it)->Audio, 0);
		_interface->AddText(((Utterance*)*it)->Foreign, 0xFFFFFFFF, 0, 0, 50, 0);
		_interface->AddText(((Utterance*)*it)->English, 0xFFFFBBBB, 0, 0, 200);
		_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);
		_interface->AddText(((Utterance*)*it)->Note, 0xFFAAAAAA, 0, 0, 50);
		_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);
		_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);
	} 
}

void TechDemo::RenderInfoPage(MSBPage* page)
{
	MSBInfoPage* pdpage = (MSBInfoPage*)page;

	// Interface code
	_interface->AddText(pdpage->Title, 0xFFFFFFFF, 0, 1, 0);
	//_interface->AddText("Skills:", 0xFFFFFFFF, 0, 0, 0);

	/*list<Skill*>::iterator its;
	for( its = pdpage->Skills.begin(); its != pdpage->Skills.end(); its++ )
		_interface->AddText(((Skill*)*its)->Name, 0xFFFF0000, 0, 2, 10);*/
	_interface->AddText(" ", 0xFFFF0000, 0, 0, 0);

	_interface->AddText(pdpage->Text, 0xFFAAAAAA, 0, 0, 205, 0);
	
	Image* im = Core::Gui->LoadJPG("ms0:/pspfw/msb/" + pdpage->Image);
	float ratio = (float)im->Width / 200;
	_interface->AddImage(im, 200, (int)(im->Height / ratio));
}

void TechDemo::RenderFullscreen()
{
	// Render ourselfs fullscreen
}
