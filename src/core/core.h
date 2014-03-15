/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: Core
# Desciption:
# This is the core class where the main thread resides. This class
# should maintain the other modules and share processing time among
# them. It will also maintain debugging output and general IO.
*/

#ifndef CORE_H
#define CORE_H

#include "../framework.h"

class Core {
	public:
	Core();
   	void Process();
   	void ProcessInput();
   	
   	public:
   		static Graphics* Gui;
   		static Controller* Ctrl;
   		static Debug* Dbg;
   		static USBManager* Usb;
   		static ModuleManager* ModMan;
   		static Config* Cfg;
   		static ConfigTheme* CfgTheme;
   		static WindowManager* WM;
   		static Desktop* Dtop;
   		static ApplicationManager* AppMan;
   		static Cursor* Mouse;
   		static Font* Fonts;
		static InfoBar* Info;
   		
   	private:
		Graphics* _gui;
   		Controller* _ctrl;
   		Debug* _dbg;
   		USBManager* _usb;
   		ModuleManager* _modMan;
   		Config* _cfg;
   		ConfigTheme* _cfgTheme;
   		WindowManager* _wm;
   		Desktop* _dTop;
   		ApplicationManager* _appMan;
   		Cursor* _mouse;
   		Font* _fonts;
		InfoBar* _info;
   		
};
#endif
