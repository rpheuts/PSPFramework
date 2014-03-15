#ifndef DESKTOP_H
#define DESKTOP_H

class Desktop{
	public:
		Desktop();
		~Desktop();
		void Render();
		void SwitchWallpaper();
		
	private:
		void LoadWallpaper(File* file);
		void CreateDesktop();
		
	private:
		FileList* _files;
		int _init;
		Image* wallpaper;
		Image* desktopData;
};
#endif
