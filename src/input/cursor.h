#include <pspctrl.h>
#include "../framework.h"

class CursorInfo{
	public:
		int CursorSpeed;
		int X;
		int Y;
		Image* Display;
};

class Cursor{
	public:
		Cursor();
		~Cursor();
		void Handle(SceCtrlData* pad);
		
	private:
		CursorInfo* cursor;
};
