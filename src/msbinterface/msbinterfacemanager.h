#ifndef INTERFACEMANAGER_H_
#define INTERFACEMANAGER_H_

#include "../framework.h"

class MSBInterfaceManager
{
	public:
		MSBInterfaceManager(WindowApp* application, Color backgroundColor);
		~MSBInterfaceManager();
		void HandleController(int analogX, int analogY, int btn);
		Image* AddContainer(MSBInterfaceContainer* container);
		Image* AddText(string text, Color color, int fontSize, int fontType, int xIndent);
		Image* AddText(string text, Color color, int fontSize, int fontType, int xIndent, int carriageReturn);
		Image* AddText(string text, Color color, int fontSize, int fontType, int xIndent, int carriageReturn, int width);
		Image* AddImage(Image* image);
		Image* AddImage(Image* image, int carriageReturn);
		Image* AddImage(Image* image, int width, int height);
		Image* AddImage(Image* image, int width, int height, int carriageReturn);
		Image* AddButton(string caption, string id, string arg);
		Image* AddButton(string caption, string id, string arg, int carriageReturn);
		Image* AddObject(MSBInterfaceObject* object);
		Image* GetScreen();
		Image* Scroll(int x, int y);
		void Clear();

	private:
		void Redraw();

	private:
		list<MSBInterfaceObject*> _objects;
		Image* _screen;
		WindowApp* _application;
		Color _backgroundColor;
		int _curDrawHeight;
		int _curDrawWidth;
		int _curMaxHeight;
		int _curScrollHeight;
		int _curScrollWidth;
};

#endif
