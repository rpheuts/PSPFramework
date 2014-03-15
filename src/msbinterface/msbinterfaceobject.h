#ifndef INTERFACEOBJECT_H_
#define INTERFACEOBJECT_H_

#include "../framework.h"

class MSBInterfaceObject
{
	public:
		MSBInterfaceObject();
		virtual ~MSBInterfaceObject() =0;
		virtual int GetHeight() =0; // Pure virtual...
		virtual int GetWidth() =0; // Pure virtual...
		virtual void Render(Image* screen, int x, int y) =0; //Pure virtual...
		virtual void RenderPart(Image* screen, int x, int y, int height, int width)=0; //Virtual...
		virtual void HandleCursor(int x, int y, int button) =0;

	public:
		int PositionX;
		int PositionY;
		int CarriageReturn;
};

#endif
