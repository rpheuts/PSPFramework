#include "../framework.h"

MSBInterfaceButton::MSBInterfaceButton(WindowApp* application, string caption, string id,  string argument)
{
	_image = Core::Gui->LoadPNG("ms0:/pspfw/btn_audio.png");
	Core::Fonts->PrintImage(caption, 10, 5, _image, 0xFFFFFFFF, 0, 1);

	_application = application;
	_id = id;
	_argument = argument;
	PositionX = 0;
	PositionY = 0;
	CarriageReturn = 1;
}

MSBInterfaceButton::~MSBInterfaceButton()
{
	delete (_image);
}

int MSBInterfaceButton::GetHeight()
{
	return _image->Height;
}

int MSBInterfaceButton::GetWidth()
{
	return _image->Width;
}

void MSBInterfaceButton::Render(Image* screen, int x, int y)
{
	Core::Gui->BlitImageToImage(0, 0, _image->Width, _image->Height, _image, x, y, screen);
}

void MSBInterfaceButton::RenderPart(Image* screen, int x, int y, int width, int height)
{
	if (height != 0 && width != 0)
		Core::Gui->BlitImageToImage(0, 0, width, height, _image, x, y, screen);
	else if (height == 0 && width != 0)
		Core::Gui->BlitImageToImage(0, 0, width, _image->Height, _image, x, y, screen);
	else if (height != 0 && width == 0)
		Core::Gui->BlitImageToImage(0, 0, _image->Width, height, _image, x, y, screen);
}

void MSBInterfaceButton::HandleCursor(int x, int y, int button)
{
	if (button == PSP_CTRL_CIRCLE)
		_application->HandleInputEvent(_id, _argument);
}
