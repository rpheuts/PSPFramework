#ifndef WINDOW_H_
#define WINDOW_H_

#include "../framework.h"

class Window
{
	public:
		Window();
		void HandleController(int mouseX, int mouseY, int btn);
		void Destroy();
		void Render();
		void RenderFullscreen();
	
	public:
		int X;
		int Y;
		int Width;
		int Height;
		int Borders;
		int Enabled;
		int ContentX;
		int ContentY;
		int Fullscreen;
		int Transparent;
		Window* Next;
		Window* Previous;
		Image* Topbar;
		WindowApp* Application;
};
#endif
