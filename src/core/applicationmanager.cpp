#include "../framework.h"
#include "../apps/techdemo.h"
#include "../apps/console.h"

ApplicationManager::ApplicationManager()
{
	TechDemo* demo = new TechDemo();
	Core::WM->CreateWindow(demo, "TLT TechDemo", 1, 0, 1);
	
	#ifdef DEBUG
	Console* console = new Console();
	Window* cons = Core::WM->CreateWindow(console, "TLM Console", 0, 0, 1);
	Core::WM->WindowPosition(cons, 100, 20);
	Core::Dbg->Log(Init, "Console Loaded...");
	#endif

	Core::Dbg->Log(Init, "Application Manager Loaded...");
}

ApplicationManager::~ApplicationManager()
{

}

void ApplicationManager::Render()
{
	
}

void ApplicationManager::HandleController(int mouseX, int mouseY, int btn)
{
	
}
