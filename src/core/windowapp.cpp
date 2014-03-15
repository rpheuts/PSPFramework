#include "../framework.h"

WindowApp::WindowApp(int width, int height)
{
	Screen = new Image(width, height);
	Width = width;
	Height = height;
}

WindowApp::~WindowApp()
{

}

void WindowApp::HandleController(int mouseX, int mouseY, int btn)
{

}

void WindowApp::HandleInputEvent(string EventID, string arg)
{

}

void WindowApp::Destroy()
{

}

void WindowApp::Render()
{

}

void WindowApp::RenderFullscreen()
{

}
