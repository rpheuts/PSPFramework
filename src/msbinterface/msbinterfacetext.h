#ifndef INTERFACETEXT_H_
#define INTERFACETEXT_H_

#include "../framework.h"

class MSBInterfaceText : public MSBInterfaceObject
{
	public:
		MSBInterfaceText(string text, Color color, int fontsize, int fontType, int xIndent);
		~MSBInterfaceText();
		void SetText(string text);
		void SetFontSize(int fontSize);
		void SetColor(Color color);
		int GetHeight();
		int GetWidth();
		void SetMaxWidth(int width);
		void Render(Image* screen, int x, int y);
		void RenderPart(Image* screen, int x, int y, int height, int width);
		void HandleCursor(int x, int y, int button);

	protected:
		string _text;
		int _fontSize;
		int _fontType;
		int _xIndent;
		int _maxWidth;
		Color _color;
};

#endif
