/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: Framework header
# Desciption:
# This header file contains all the component headers of the framework
# and thus provides all the functionality supported by the framework.
*/

// #define DEBUG
// #define WINDOW_TITLES

#ifndef ARTILLERY_H_
#define ARTILLERY_H_

#define MK8888(b,g,r,a) (((b&0xFF)<<16) + ((g&0xFF)<<8) + ((r&0xFF)) + ((a&0xFF)<<24))
#define IS_ALPHA(color) ((color)&0xFF000000?0:1)
#define IS_RED(color) ((color)&0x000000FF?1:0)
#define GET_ALPHA(c) ((unsigned short)((c & 0xFF000000) >> 24))
#define GET_RED(c) ((unsigned short)((c & 0x000000FF)))
#define GET_GREEN(c) ((unsigned short)((c & 0x0000FF00) >> 8))
#define GET_BLUE(c) ((unsigned short)((c & 0x00FF0000)>>16))
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define PSP_LINE_SIZE 512

#define THEME_PATH "ms0:/pspfw/themes/"
#define THEME_FILE "/theme.cfg"

#include <psptypes.h>
typedef u32 Color;

#include <string>
#include <list>
using namespace std;

// Config
#include "config/config.h"
#include "config/configtheme.h"

// FileIO
#include "core/fileio.h"

// Graphics
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/font.h"

// Windowing
#include "core/windowapp.h"
#include "core/window.h"
#include "utils/interface.h"
#include "core/windowmanager.h"

// Audio
#include "audio/playbackmp3.h"

//Input
#include "input/controller.h"
#include "input/cursor.h"

//Misc
#include "debug/debug.h"
#include "core/usbmanager.h"
#include "core/modulemanager.h"
#include "msbinterface/msbinterface.h"

//XML
#include "xml/tinyxml.h"
#include "msbparse/msbparse.h"

// Core
#include "core/desktop.h"
#include "core/applicationmanager.h"
#include "core/infobar.h"
#include "core/core.h"

#endif
