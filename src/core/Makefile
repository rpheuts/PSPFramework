TARGET = core
OBJS =	main.o core.o usbmanager.o modulemanager.o fileio.o infobar.o\
	../graphics/image.o ../graphics/graphics.o ../input/controller.o ../debug/debug.o \
	../config/config.o ../audio/playbackmp3.o windowapp.o window.o windowmanager.o \
	../config/configtheme.o desktop.o applicationmanager.o ../apps/console.o ../input/cursor.o \
	../graphics/font_new.o ../apps/techdemo.o ../xml/tinystr.o ../xml/tinyxmlerror.o ../xml/tinyxmlparser.o \
	../xml/tinyxml.o ../msbparse/msbpassivedialog.o ../msbparse/msbparser.o ../msbinterface/msbinterfacecontainer.o \
	../msbinterface/msbinterfacetext.o ../msbinterface/msbinterfaceobject.o ../msbinterface/msbinterfacemanager.o \
	../msbparse/msbpronunciation.o ../msbinterface/msbinterfaceimage.o ../msbinterface/msbinterfacebutton.o \
	../msbparse/msbinfo.o

USE_PSPSDK_LIBC = 1

BUILD_PRX = 1

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS) -c

LIBDIR =
LDFLAGS = 

LIBS = -lpspgu -lpsprtc -lpng -ljpeg -lz -lpsphprm \
	-lpspusb -lpspusbstor -lpspumd -lpspaudiolib -lpspaudio -lmad -lstdc++ -lm -lc
	
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak