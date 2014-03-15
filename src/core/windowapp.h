#ifndef WINDOWAPP_H_
#define WINDOWAPP_H_

#include "../framework.h"

class WindowApp
{
	public:
		WindowApp(int width, int height);
		virtual ~WindowApp();
		virtual void HandleController(int mouseX, int mouseY, int btn);
		virtual void HandleInputEvent(string EventID, string arg);
		virtual void Destroy();
		virtual void Render();
		virtual void RenderFullscreen();
		
	public:
		Image* Screen;
		int Width;
		int Height;
};
#endif
