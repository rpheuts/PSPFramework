#include "../framework.h"

Window::Window()
{

}

void Window::HandleController(int mouseX, int mouseY, int btn)
{
	if (Application != NULL)
		Application->HandleController(mouseX, mouseY, btn);
}

void Window::Destroy()
{
	if (Application != NULL)
		Application->Destroy();
}

void Window::Render()
{
	if (Application != NULL)
		Application->Render();
}

void Window::RenderFullscreen()
{
	if (Application != NULL)
		Application->RenderFullscreen();
}
