/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: Controller
# Desciption:
# Provides access to the buttons and the ananlog stick of the PSP.
*/

#include <pspctrl.h>

class Controller{
	public:
		Controller();
		void Handle(SceCtrlData* pad);
		
	public:
		int LastInput;
		int PreviousInput;
		int LastInputRemote;
		int PreviousInputRemote;
		int IsLastInputPressedRemote;
		int IsLastInputPressed;
		int AnalogX;
		int AnalogY;
		int PreviousAnalogX;
		int PreviousAnalogY;
		int Handled;
		int RemotePluggedIn;

};


