#ifndef FONT_H_
#define FONT_H_
#include "../framework.h"

class Font{
	public:
		Font();
		~Font();
		int GetFontWidth(int fontSize);
		int GetFontHeight(int fontSize);
		int PrintScreen(const char* text, int x, int y, Color color, int fontSize);
		int PrintImage(const char* text, int x, int y, Image* image, Color color, int fontSize);
		int PrintScreen(string text, int x, int y, Color color, int fontSize);
		int PrintImage(string text, int x, int y, Image* image, Color color, int fontSize);
		int PrintImage(char ch, int x, int y, Image* image, Color color, int fontSize);
		int PrintScreen(const char* text, int x, int y, Color color, int fontSize, int alpha);
		int PrintImage(const char* text, int x, int y, Image* image, Color color, int fontSize, int alpha);
	
	private:
		int Print(const char* text, int x, int y, Color color, int fontSize, Color* dest, int line_size, int alpha);
		int PrintLetter(char c, int x, int y, int fontSize, Color color, Color* dest, int line_size, int alpha);
		int GetLetterWidth(char c, int fontSize);
		int GetLetterPosition(char c, int fontSize);
};
#endif /*FONT_H_*/
