#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "../framework.h"
class Console : public WindowApp
{
	public:
		Console();
		~Console();
		void HandleController(int mouseX, int mouseY, int btn);
		void HandleInputEvent(string EventID, string arg);
		void Destroy();
		void Render();
		void RenderFullscreen();
		void ProcessDebug();
		void Print(string text, Color color, int fontSize);
		void Print(string text, Color color, int fontSize, int fontType);
		
	private:
		int _cursorY;
};
#endif
