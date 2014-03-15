#include <pspmoduleinfo.h> 
#include <pspaudiolib.h>
#include <pspctrl.h>
#include <psppower.h>
#include <pspdebug.h>
#include "../framework.h"

// Define printf, just to make typing easier
#define printf	pspDebugScreenPrintf
#define CFG_FILE "ms0:/pspfw/config/main.cfg"
PSP_MODULE_INFO("COREPRX", 0, 1, 0);
PSP_HEAP_SIZE_KB(15360);

Debug* Core::Dbg;
Graphics* Core::Gui;
Controller* Core::Ctrl;
USBManager* Core::Usb;
ModuleManager* Core::ModMan;
Config* Core::Cfg;
ConfigTheme* Core::CfgTheme;
WindowManager* Core::WM;
Desktop* Core::Dtop;
ApplicationManager* Core::AppMan;
Cursor* Core::Mouse;
Font* Core::Fonts;
InfoBar* Core::Info;

static SceCtrlData pad;

Core::Core()
{
	// Open config files
	_cfg = new Config(CFG_FILE);
	Cfg = _cfg;
	_cfgTheme = new ConfigTheme();
	CfgTheme = _cfgTheme;
	
	// Init the components
	_dbg = new Debug();
	Dbg = _dbg;
	_dbg->Log(Init, "Loading core...");
	_dbg->Log(Init, "Core Version: 0.1");
	_dbg->Log(Init, "Core Memory : 15360Kb");
	_dbg->Log(Init, " ");
	_dbg->Log(Init, "Init Stage 1");
	_dbg->Log(Init, "Configs Loaded...");
	
	_gui = new Graphics(SCREEN_WIDTH, SCREEN_HEIGHT, 512);
	Gui = _gui;
	
	_wm = new WindowManager();
	WM = _wm;
	
	_ctrl = new Controller();
	Ctrl = _ctrl;
	
	_usb = new USBManager();
	Usb = _usb;
	
	_modMan = new ModuleManager();
	ModMan = _modMan;
	
	_dbg->Log(Init, "Core Components loaded...");
	_dbg->Log(Init, " ");
	_dbg->Log(Init, "Init Stage 2");
	
	_fonts = new Font();
	Fonts = _fonts;
	
	_mouse = new Cursor();
	Mouse = _mouse;
	
	_dTop = new Desktop();
	Dtop = _dTop;
	
	_appMan = new ApplicationManager();
	AppMan = _appMan;

	_info = new InfoBar();
	Info = _info;
	
	pspAudioInit();
	_dbg->Log(Init, "Audio Loaded... ");
	
	_dbg->Log(Init, " ");
	_usb->ToggleUSB();
}

/* Main core function */
void Core::Process()
{
	// Read in current control info
	sceCtrlReadBufferPositive(&pad, 1);
	
	// Render the shell components
	_dTop->Render();
	_wm->Render();
	_info->Render();
	
	// Handle the controller
	_ctrl->Handle(&pad);
	_mouse->Handle(&pad);
	_wm->Handle();
	ProcessInput();
	
	// Update screen
	_gui->WaitVblankStart();
	_gui->FlipScreen();
}

void Core::ProcessInput()
{
	if (_ctrl->LastInput == PSP_CTRL_START)
		if (_ctrl->IsLastInputPressed != 1)
			_usb->ToggleUSB();
	if (_ctrl->LastInput == PSP_CTRL_SELECT)
		if (_ctrl->IsLastInputPressed != 1)
			_modMan->Reboot();
}
