#include "../framework.h"

MSBInterfaceText::MSBInterfaceText(string text, Color color, int fontSize, int fontType, int xIndent)
{
	_text = text;
	_fontSize = fontSize;
	_fontType = fontType;
	_color = color;
	_xIndent = xIndent;
	PositionX = 0;
	PositionY = 0;
	CarriageReturn = 1;
	_maxWidth = SCREEN_WIDTH;
}

MSBInterfaceText::~MSBInterfaceText()
{
	
}

void MSBInterfaceText::SetText(string text)
{
	_text = text;
}

void MSBInterfaceText::SetMaxWidth(int width)
{
	_maxWidth = width;
}

void MSBInterfaceText::SetFontSize(int fontSize)
{
	_fontSize = fontSize;
}

void MSBInterfaceText::SetColor(Color color)
{
	_color = color;
}

int MSBInterfaceText::GetHeight()
{
	return Core::Fonts->GetFontHeight(_fontSize) + 1;
}

int MSBInterfaceText::GetWidth()
{
	return Core::Fonts->GetFontHeight(_fontSize) * _text.length() + 1;
}

void MSBInterfaceText::Render(Image* screen, int x, int y)
{
	x += _xIndent;
	int count = 0;
	int carretX = x;
	int textLength = _text.length();
	int _cursorY = y;
	int fontWidth = Core::Fonts->GetFontWidth(_fontSize);

	while (count < textLength)
	{
		if (_text[count] == '\n' || (carretX + fontWidth) > _maxWidth)
		{
			_cursorY += Core::Fonts->GetFontHeight(_fontSize)+1;
			carretX = x;
			if (_text[count] == '\n')
				count++;
			continue;
		}
		
		char ch = _text[count];
		if (ch == ' ')
			carretX += fontWidth;
		else
			carretX += Core::Fonts->PrintImage(ch, carretX, _cursorY, screen, _color, _fontSize, _fontType) + 1;
		count++;
	}
}

void MSBInterfaceText::RenderPart(Image* screen, int x, int y, int height, int width)
{
	// ToDo
}

void MSBInterfaceText::HandleCursor(int x, int y, int button)
{
	// Nothing to handle for text yet...
}
