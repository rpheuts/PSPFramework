#ifndef APPMANAGER_H
#define APPMANAGER_H

#include "../framework.h"

class ApplicationManager
{
	public:
		ApplicationManager();
		~ApplicationManager();
		void Render();
		void HandleController(int mouseX, int mouseY, int btn);
};
#endif
