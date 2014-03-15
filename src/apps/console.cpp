#include "../framework.h"
#include "console.h"

#define WINDOW_WIDTH 260
#define WINDOW_HEIGHT 240

Console::Console() : WindowApp(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	// Init graphics
	Core::Gui->ClearImage(0xFF2E3F45, Screen);
	_cursorY = 0;
}

Console::~Console()
{
	// Clean up
}

void Console::HandleController(int mouseX, int mouseY, int btn)
{

}

void Console::HandleInputEvent(string EventID, string arg)
{

}

void Console::Destroy()
{
	// Prepare for window close
}

void Console::Render()
{
	ProcessDebug();
}

void Console::RenderFullscreen()
{
	// Render ourselfs fullscreen
}

void Console::ProcessDebug()
{
	// Pop debug messages from the buffer and print them to the screen
	DebugMessage* msg = Core::Dbg->Pop();
	if (!msg)
		return;
	switch (msg->Type)
	{
		case Error:
			Print("[Error] " + msg->Message, 0xFF0000FF, 0);
		break;
		
		case Warning:
			Print("[Warning]" + msg->Message, 0xFF00FF00, 0);
		break;
		
		case Init:
			Print(msg->Message, 0xFFCCFFCC, 0);
		break;
		
		case Text:
		default:
			Print("[Message] " + msg->Message, 0xFFFFFFFF, 0);
		break;
	}
		
}

void Console::Print(string text, Color color, int fontSize)
{
	Print(text, color, fontSize, 0);
}

void Console::Print(string text, Color color, int fontSize, int fontType)
{
	// Check if we reached the end of the window, if so clear the screen and start at the top
	if (_cursorY >= WINDOW_HEIGHT)
	{
		Core::Gui->ClearImage(0xBB2E3F45, Screen);
		_cursorY = 0;
	}

	int carretX = 1;
	int count = 0;
	int fontWidth = Core::Fonts->GetFontWidth(fontSize);
	int textLength = text.length();
	
	// Try printing each letter, checking if we reached the side of the screen, if so move to the next line
	while (count < textLength)
	{
		if (text[count] == '\n' || (carretX + fontWidth) > WINDOW_WIDTH)
		{
			if ((_cursorY + 6) > WINDOW_HEIGHT)
				break;
			_cursorY += Core::Fonts->GetFontHeight(fontSize)+1;
			carretX = 1;
			if (text[count] == '\n')
				count++;
			continue;
		}
		
		char ch = text[count];
		if (ch == ' ')
			carretX += fontWidth;
		else
			carretX += Core::Fonts->PrintImage(ch, carretX, _cursorY, Screen, color, fontSize, fontType) + 1;
		count++;
	}
	_cursorY += Core::Fonts->GetFontHeight(fontSize)+1;
}
