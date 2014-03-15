#ifndef INTERFACEIMAGE_H_
#define INTERFACEIMAGE_H_

#include "../framework.h"

class MSBInterfaceImage : public MSBInterfaceObject
{
	public:
		MSBInterfaceImage(Image* image);
		~MSBInterfaceImage();
		int GetHeight();
		int GetWidth();
		void Render(Image* screen, int x, int y);
		void RenderPart(Image* screen, int x, int y, int width, int height);
		void HandleCursor(int x, int y, int button);

	protected:
		Image* _image;
};

#endif
