/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: USBManager
# Desciption:
# Provides access to the USB functionality of the PSP. Can check if
# USB is currently enabled anf can toggle the USB function on and off.
*/

class USBManager{
	public:
		USBManager();
		void ToggleUSB();
		void ToggleUSB(int silent);
		bool IsEnabled();
};
