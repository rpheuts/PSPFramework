#include "../framework.h"
#include <pspctrl.h>


void Desktop::LoadWallpaper(File* file)
{
	Image* tmp;
	if (file->Filename.find("png") != string::npos)
		tmp = Core::Gui->LoadPNG(file->FullPath.c_str());
	else if (file->Filename.find("jpg") != string::npos)
		tmp = Core::Gui->LoadJPG(file->FullPath.c_str());
	else if (file->Filename.find("PNG") != string::npos)
		tmp = Core::Gui->LoadPNG(file->FullPath.c_str());
	else if (file->Filename.find("JPG") != string::npos)
		tmp = Core::Gui->LoadJPG(file->FullPath.c_str());
	else
		return;
	
	Core::Gui->ResizeImage(SCREEN_WIDTH, SCREEN_HEIGHT, tmp, wallpaper);
	Core::Gui->FreeImage(tmp);
}

void Desktop::Render()
{
	Core::Gui->BlitImageToScreen(0, 0, 480, 272, desktopData, 0, 0);
}

void Desktop::CreateDesktop()
{
	Core::Gui->BlitImageToImage(0, 0, 480, 272, wallpaper, 0, 0,desktopData);
}

void Desktop::SwitchWallpaper()
{
	if(_files->FileCount() > 0)
	{
		File* file = _files->GetCurrentFile();
		if (!file)
		{
			_files->Reset();
			file = _files->GetCurrentFile();
			if (!file)
				return;
		}
		LoadWallpaper(file);
		CreateDesktop();
		_files->GetNextFile();
	}
}

Desktop::Desktop()
{
	desktopData = Core::Gui->CreateImage(480,272);
	wallpaper = Core::Gui->CreateImage(480,272);
	File* file = new File("wallpaper.png", "ms0:/pspfw/wallpapers/");
	LoadWallpaper(file);
	CreateDesktop();
	
	Core::Dbg->Log(Init, "Desktop Loaded...");
}

Desktop::~Desktop()
{
	//_files->Clear();
	Core::Gui->FreeImage(desktopData);
	Core::Gui->FreeImage(wallpaper);
	_init = 0;
}
