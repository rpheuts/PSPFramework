#ifndef INTERFACECONTAINER_H_
#define INTERFACECONTAINER_H_

#include "../framework.h"

class MSBInterfaceContainer : public MSBInterfaceObject
{
	public:
		MSBInterfaceContainer();
		~MSBInterfaceContainer();
		void AddText(string text, Color color);
		void AddImage(Image* image);
		void AddImage(Image* image, int width, int height);
		void AddObject(MSBInterfaceContainer*);
		int GetHeight();
		int GetWidth();
		void Render(Image* screen, int x, int y);
		void RenderPart(Image* screen, int x, int y, int height, int width);
		void HandleCursor(int x, int y, int button);

	protected:
		list<MSBInterfaceObject*> _objects;
};

#endif
