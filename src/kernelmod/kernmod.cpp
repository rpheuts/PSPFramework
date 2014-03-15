/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: Kernmod.prx
# Desciption:
# This module provides a basic module/application loading
# functionality. It can reboot the shell or pass control to the next
# loader module which actually starts an UMD or loads an application,
# and hooks the sceKernelExitGame function.
*/


#include <pspkernel.h>
#include <pspdebug.h>
#include <pspiofilemgr.h>
#include <pspsdk.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <psploadexec.h>

#include <pspdebug.h>

#define MODULE_NAME		"KERNMOD"
#define VERSION 		"0.1"

#define printf	pspDebugScreenPrintf
#define DEBUG

PSP_MODULE_INFO(MODULE_NAME, 0x1000, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

const char test[5] = "laat";

//////////////////////////////////////////////////////////////////////
// Module Entry Point
//////////////////////////////////////////////////////////////////////
int main(int args, char **argp)
{
	if (args > 0)
	{
		if (strstr(argp[0], "reboot"))
			sceKernelLoadExec("ms0:/pspfw/pspfw.elf", NULL);	
		char* path = (char *) malloc(sizeof(argp[0])); 
		strcpy(path, argp[0]);
	
		struct SceKernelLoadExecParam	execParam;
		const u32 total_length = strlen(argp[0]) + 1;

		execParam.args = total_length;
		execParam.argp = const_cast< char * >( argp[0] );
		execParam.key = NULL;
		execParam.size = sizeof( execParam ) + total_length;
	
		sceKernelLoadExec("ms0:/MbShell/modules/bootloader.elf", &execParam);
	}
	
	sceKernelLoadExec("ms0:/MbShell/modules/bootloader.elf", NULL);
	sceKernelExitDeleteThread(0);
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Module Exit Point
//////////////////////////////////////////////////////////////////////
int module_stop(SceSize args, void *argp)
{
	//sceKernelExitDeleteThread(0);

	return 0;
}


