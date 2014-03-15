#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "../framework.h"

class WindowManager{
	public:
		WindowManager();
		~WindowManager();
		Window* CreateWindow(WindowApp* application, char * name, int transparent, int fullscreen, int borders);
		void Render();
		void Focus(Window* window);
		void DestroyWindow(Window* window);
		void Handle();
		void WindowPosition(Window* window, int x, int y);
		
	public:
		int FullScreenEnabled;
		
	private:
		void HandleFocus();
		void HandleDrag();
		void HandleController();
		void RegisterWindow(Window* window);
		
	private:
		static Window* ListStart;
		static Window* ListEnd;
		Image* InitTopbar(int width, char * text);
		int createdLastX;
		int createdLastY;
		int IsBeingDragged;
		int IsActive;
		Image* shadow_h;
		Image* shadow_v_r;
		Image* shadow_v_l;
		Image* shadow_c_r;
		Image* shadow_c_l;
		Image* wnd_btn_close;
		Image* wnd_img_left;
		Image* wnd_img_right;
		Image* wnd_img_center;
		Image* wnd_img_scale_left;
		Image* wnd_img_scale_right;
		int titlebartextoffsetx;
		int titlebartextoffsety;
};
#endif
