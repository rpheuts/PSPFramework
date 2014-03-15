#include "../framework.h"

MSBInterfaceObject::MSBInterfaceObject()
{

}

MSBInterfaceObject::~MSBInterfaceObject()
{

}

int MSBInterfaceObject::GetHeight()
{
	//Should've been handled by the inherited object!
	return 0;
}

int MSBInterfaceObject::GetWidth()
{
	//Should've been handled by the inherited object!
	return 0;
}

void MSBInterfaceObject::Render(Image* screen, int x, int y)
{
	//Should've been handled by the inherited object!
}

void RenderPart(Image* screen, int x, int y, int height, int width)
{
	// Can be handled by the inherited object, otherwise lets do nothing...
}

void MSBInterfaceObject::HandleCursor(int x, int y, int button)
{
	//Should've been handled by the inherited object!
}
