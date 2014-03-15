#include "../framework.h"

MSBInterfaceImage::MSBInterfaceImage(Image* image)
{
	_image = image;
	PositionX = 0;
	PositionY = 0;
	CarriageReturn = 1;
}

MSBInterfaceImage::~MSBInterfaceImage()
{
	
}

int MSBInterfaceImage::GetHeight()
{
	return _image->Height;
}

int MSBInterfaceImage::GetWidth()
{
	return _image->Width;
}

void MSBInterfaceImage::Render(Image* screen, int x, int y)
{
	if (!_image)
		return;

	Core::Gui->BlitImageToImage(0, 0, _image->Width, _image->Height, _image, x, y, screen);
}

void MSBInterfaceImage::RenderPart(Image* screen, int x, int y, int width, int height)
{
	if (!_image)
		return;

	if (height != 0 && width != 0)
		Core::Gui->BlitImageToImage(0, 0, width, height, _image, x, y, screen);
	else if (height == 0 && width != 0)
		Core::Gui->BlitImageToImage(0, 0, width, _image->Height, _image, x, y, screen);
	else if (height != 0 && width == 0)
		Core::Gui->BlitImageToImage(0, 0, _image->Width, height, _image, x, y, screen);
}

void MSBInterfaceImage::HandleCursor(int x, int y, int button)
{

}
