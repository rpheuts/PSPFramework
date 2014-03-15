#ifndef INFOBAR_H_
#define INFOBAR_H_

#include "../framework.h"

class InfoBar
{
	public:
		InfoBar();
		~InfoBar();
		void Render();

	private:
		Image* _bar;
};

#endif
