#include "../framework.h"

#define BORDER_HEIGHT 2
#define BORDER_WIDTH 2

MSBInterfaceManager::MSBInterfaceManager(WindowApp* application, Color backgroundColor)
{
	_screen = application->Screen;
	_application = application;
	_curDrawWidth = BORDER_WIDTH;
	_curDrawHeight = BORDER_HEIGHT;
	_curScrollHeight = BORDER_HEIGHT;
	_curScrollWidth = BORDER_WIDTH;
	_curMaxHeight = BORDER_HEIGHT;
	_backgroundColor = backgroundColor;

}
MSBInterfaceManager::~MSBInterfaceManager()
{

}

void MSBInterfaceManager::HandleController(int analogX, int analogY, int btn)
{
	list<MSBInterfaceObject*>::iterator it;
	analogY += _curScrollHeight;
	for( it = _objects.begin(); it != _objects.end(); it++ )
	{
		int y = ((MSBInterfaceObject*)*it)->PositionY;
		int height = ((MSBInterfaceObject*)*it)->GetHeight();
		if (analogY > y && analogY < (y + height))
			((MSBInterfaceObject*)*it)->HandleCursor(analogX, analogY, btn);
	}
}

Image* MSBInterfaceManager::Scroll(int x, int y)
{
	// Check if we are still within bounds of the content
	if (y != 0 && ((_curScrollHeight + y) >= BORDER_HEIGHT) && (_curScrollHeight + y) <= (_curMaxHeight))
	{
		_curScrollHeight += y;
		Redraw();
	}
	if (x != 0 && (_curScrollWidth + x) >= BORDER_WIDTH)
	{
		_curScrollWidth += x;
		Redraw();
	}
	return _screen;
}

Image* MSBInterfaceManager::AddContainer(MSBInterfaceContainer* container)
{
	container->CarriageReturn = 1;
	AddObject(container);
	return _screen;
}

Image* MSBInterfaceManager::AddText(string text, Color color, int fontSize, int fontType, int xIndent)
{
	return AddText(text, color, fontSize, fontType, xIndent, 1);
}

Image* MSBInterfaceManager::AddText(string text, Color color, int fontSize, int fontType, int xIndent, int carriageReturn)
{
	
	return AddText(text, color, fontSize, fontType, xIndent, carriageReturn, _screen->Width);
}

Image* MSBInterfaceManager::AddText(string text, Color color, int fontSize, int fontType, int xIndent, int carriageReturn, int width)
{
	MSBInterfaceText* txt = new MSBInterfaceText(text, color, fontSize, fontType, xIndent);
	txt->CarriageReturn = carriageReturn;
	txt->SetMaxWidth(width);
	AddObject(txt);
	return _screen;
}

Image* MSBInterfaceManager::AddImage(Image* image)
{
	return AddImage(image, 1);
}

Image* MSBInterfaceManager::AddImage(Image* image, int carriageReturn)
{
	MSBInterfaceImage* img = new MSBInterfaceImage(image);
	img->CarriageReturn = carriageReturn;
	AddObject(img);
	return _screen;
}

Image* MSBInterfaceManager::AddImage(Image* image, int width, int height)
{
	return AddImage(image, width, height, 1);
}

Image* MSBInterfaceManager::AddImage(Image* image, int width, int height, int carriageReturn)
{
	MSBInterfaceImage* img = new MSBInterfaceImage(Core::Gui->ResizeImage(width, height, image));
	img->CarriageReturn = carriageReturn;
	AddObject(img);
	return _screen;
}

Image* MSBInterfaceManager::AddButton(string caption, string id, string arg)
{
	return AddButton(caption, id, arg, 1);
}

Image* MSBInterfaceManager::AddButton(string caption, string id, string arg, int carriageReturn)
{
	MSBInterfaceButton* btn = new MSBInterfaceButton(_application, caption, id, arg);
	btn->CarriageReturn = carriageReturn;
	AddObject(btn);
	return _screen;
}

Image* MSBInterfaceManager::AddObject(MSBInterfaceObject* object)
{
	_objects.push_back(object);
	if ((_curDrawHeight + object->GetHeight()) <= _screen->Height)
	{
		//object->Render(_screen, _curDrawWidth, _curDrawHeight);
		object->PositionX = _curDrawWidth;
		object->PositionY = _curDrawHeight;
		_curDrawHeight += object->GetHeight();
	}
	_curMaxHeight += object->GetHeight();
	Redraw();
	return _screen;
}

Image* MSBInterfaceManager::GetScreen()
{
	return _screen;
}

void MSBInterfaceManager::Redraw()
{
	_curDrawHeight = BORDER_HEIGHT;
	int height = 0, scrollSkip = BORDER_HEIGHT;
	
	// Clear screen
	Core::Gui->ClearImage(_backgroundColor, _screen);

	list<MSBInterfaceObject*>::iterator it;
	for( it = _objects.begin(); it != _objects.end(); it++ )
	{	
		height = ((MSBInterfaceObject*)*it)->GetHeight();
		if (scrollSkip  >= _curScrollHeight)
		{
			if ((_curDrawHeight + height) <= _screen->Height)
			{
				((MSBInterfaceObject*)*it)->Render(_screen, _curDrawWidth, _curDrawHeight);
				if (((MSBInterfaceObject*)*it)->CarriageReturn == 1)
					_curDrawHeight += height;
			}
			else if (_curDrawHeight < _screen->Height)
			{
				// Doesn't fit, offer to render just part of the object
				((MSBInterfaceObject*)*it)->RenderPart(_screen, _curDrawWidth, _curDrawHeight, 0, _screen->Height - _curDrawHeight);
				if (((MSBInterfaceObject*)*it)->CarriageReturn == 1)
					_curDrawHeight += _screen->Height - _curDrawHeight;
			}
		}
		if (((MSBInterfaceObject*)*it)->CarriageReturn == 1)
			scrollSkip += height;
	}
}

void MSBInterfaceManager::Clear()
{
	_objects.clear();
	_curDrawWidth = BORDER_WIDTH;
	_curDrawHeight = BORDER_HEIGHT;
	_curScrollHeight = BORDER_HEIGHT;
	_curScrollWidth = BORDER_WIDTH;
	_curMaxHeight = BORDER_HEIGHT;
}
