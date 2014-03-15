#ifndef INTERFACE_H
#define INTERFACE_H

#include "../framework.h"

class Interface{
	public:
		static inline bool Interface::IsWithinWindow(int x, int y, Window* window)
		{
			if (!window->Fullscreen)
				return IsWithinArea(x, y, window->X, window->Y, window->Width, window->Height);
			else
		return true;
		}

		static inline bool Interface::IsWithinWindowContent(int x, int y, Window* window)
		{
			if (!window->Fullscreen)
				return IsWithinArea(x, y, window->ContentX, window->ContentY, window->Application->Screen->Width, window->Application->Screen->Height);
			else
				return true;
		}

		static inline bool Interface::IsWithinImage(int x, int y, int tx, int ty, Image* image)
		{
			return IsWithinArea(x, y, tx, ty, image->Width, image->Height);
		}

		static inline bool Interface::IsWithinArea(int x, int y, int tx, int ty, int tWidth, int tHeight)
		{
			if (x > tx)
			{
				if (y > ty)
				{
					if (x < (tx + tWidth))
					{
						if (y < (ty + tHeight))
							return true;
						else
							return false;
					}
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
};
#endif
