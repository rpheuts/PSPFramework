/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: ModuleManager
# Desciption:
# Provides functionality concerning modules. It supports the loading
# of other modules and starting of other applications. The latter is
# provided by an external module (kernmod.prx) because kernel-mode is
# needed. This module also provides a hook to the sceKernelExitGame
# function. Finally this class provides a reboot function to reboot
# the current aplication (usually used for debugging).
*/

class ModuleManager{
	public:
		ModuleManager();
		int LoadStartModule(string path, string arg);
		void LoadStartUMD();
		void LoadStartELF(string elf);
		void Reboot();
};
