#ifndef FONT_H_
#define FONT_H_
#include "../framework.h"

class Font{
	public:
		Font();
		~Font();
		int GetFontWidth(int fontSize);
		int GetFontHeight(int fontSize);
		int PrintScreen(const char* text, int x, int y, Color color, int fontSize, int fontType);
		int PrintImage(const char* text, int x, int y, Image* image, Color color, int fontSize, int fontType);
		int PrintScreen(string text, int x, int y, Color color, int fontSize, int fontType);
		int PrintImage(string text, int x, int y, Image* image, Color color, int fontSize, int fontType);
		int PrintScreen(string text, int x, int y, Color color, int fontSize);
		int PrintImage(string text, int x, int y, Image* image, Color color, int fontSize);
		int PrintImage(char ch, int x, int y, Image* image, Color color, int fontSize, int fontType);
		int PrintScreen(const char* text, int x, int y, Color color, int fontSize, int fontType, int alpha);
		int PrintImage(const char* text, int x, int y, Image* image, Color color, int fontSize, int fontType, int alpha);

	private:
		int GetCharacterPositionX(char c, int fontSize);
		int GetCharacterPositionY(char c, int fontSize, int fontType);
		int GetPunctuationPositionX(char c, int fontSize);
		int GetCharacterWidth(char c, int fontSize, int fontType);
		int PrintLetter(char c, int x, int y, int fontSize, int fontType, Color color, Color* dest, int line_size, int alpha);
		int Print(const char* text, int x, int y, Color color, int fontSize, int fontType, Color* dest, int line_size, int alpha);
	
	private:
		int _gridWidth[4];
		int _gridHeight[4];
		int _fontWidth[4];
		int _fontTypePostionCapital[3];
		int _fontTypePostionSmall[3];
		int _fontTypePostionPunctuation[3];
		Image* fontSmall;
};
#endif /*FONT_H_*/
