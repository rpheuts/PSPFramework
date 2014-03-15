#ifndef INTERFACEBUTTON_H_
#define INTERFACEBUTTON_H_

#include "../framework.h"

class MSBInterfaceButton : public MSBInterfaceObject
{
	public:
		MSBInterfaceButton(WindowApp* application, string caption, string id,  string argument);
		~MSBInterfaceButton();
		int GetHeight();
		int GetWidth();
		void Render(Image* screen, int x, int y);
		void RenderPart(Image* screen, int x, int y, int width, int height);
		void HandleCursor(int x, int y, int button);

	protected:
		Image* _image;
		WindowApp* _application;
		string _id;
		string _argument;
};

#endif
