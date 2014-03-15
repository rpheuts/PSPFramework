#include "../framework.h"

int MSBInterfaceContainer::GetHeight()
{
	int height = 0;
	list<MSBInterfaceObject*>::iterator it;

	for( it = _objects.begin(); it != _objects.end(); it++ )
		height += ((MSBInterfaceObject*)*it)->GetHeight();

	return height;
}

int MSBInterfaceContainer::GetWidth()
{
	int height = 0;
	list<MSBInterfaceObject*>::iterator it;

	for( it = _objects.begin(); it != _objects.end(); it++ )
		height += ((MSBInterfaceObject*)*it)->GetWidth();

	return height;
}

void MSBInterfaceContainer::Render(Image* screen, int x, int y)
{
	int curHeight = y;
	list<MSBInterfaceObject*>::iterator it;

	for( it = _objects.begin(); it != _objects.end(); it++ )
	{	
		((MSBInterfaceObject*)*it)->Render(screen, x, curHeight);
		curHeight += ((MSBInterfaceObject*)*it)->GetHeight();
	}
}

void MSBInterfaceContainer::RenderPart(Image* screen, int x, int y, int height, int width)
{

}
