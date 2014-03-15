#include <malloc.h>
#include <string.h>
#include <pspctrl.h>

#include "../framework.h"

Window* WindowManager::ListStart;
Window* WindowManager::ListEnd;

WindowManager::WindowManager()
{
	createdLastX = 5;
	createdLastY = 2;
	titlebartextoffsetx = 0;
	titlebartextoffsety = 0;
	shadow_h = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndborderhor").c_str());
	shadow_v_r = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndborderverright").c_str());
	shadow_v_l = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndborderverleft").c_str());
	shadow_c_r = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndbordercorright").c_str());
	shadow_c_l = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndbordercorleft").c_str());
	wnd_btn_close = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndtopbarbtn").c_str());
	wnd_img_left = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndtopbarleft").c_str());
	wnd_img_right = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndtopbarright").c_str());
	wnd_img_center = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndtopbarcenter").c_str());
	wnd_img_scale_left = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndtopbarscaleleft").c_str());
	wnd_img_scale_right = Core::Gui->LoadPNG(Core::CfgTheme->GetPathValue("c_wndtopbarscaleright").c_str());
	Core::CfgTheme->GetIntValue("titlebartextoffsetx", titlebartextoffsetx);
	Core::CfgTheme->GetIntValue("titlebartextoffsety", titlebartextoffsety);
	Core::Dbg->Log(Init, "Window Manager loaded...");
}

WindowManager::~WindowManager()
{
	Core::Gui->FreeImage(shadow_h);
	Core::Gui->FreeImage(shadow_v_r);
	Core::Gui->FreeImage(shadow_v_l);
	Core::Gui->FreeImage(shadow_c_r);
	Core::Gui->FreeImage(shadow_c_l);
	Core::Gui->FreeImage(wnd_btn_close);
	Core::Gui->FreeImage(wnd_img_left);
	Core::Gui->FreeImage(wnd_img_right);
	Core::Gui->FreeImage(wnd_img_center);
	Core::Gui->FreeImage(wnd_img_scale_left);
	Core::Gui->FreeImage(wnd_img_scale_right);
	
	Window* t = ListEnd;
	while (t)
	{
		DestroyWindow(t);
		t = t->Previous;
	}
}

void WindowManager::DestroyWindow(Window* window)
{
	window->Destroy();
	if (window->Application->Screen)
		delete (window->Application->Screen);
	delete (window->Topbar);
	
	Window* t = ListStart;
	Window* cur = NULL;
	Window* prev= NULL;

	if (window == ListStart)
	{
		ListStart = t->Next;
		if (t->Next)
			t->Next->Previous = NULL;
		if (window == ListEnd)
			ListEnd = NULL;
		free(t);
		return;
	}
	
	while (t && t->Next)
	{
		if (t->Next == window)
		{
			cur = t->Next;
			prev = t;
			break;
		}
		t = t->Next;
	}
	if (cur == ListEnd)
			ListEnd = prev;
	prev->Next = cur->Next;
	cur->Next->Previous = prev;
	free(cur);
	free(window);
}

void WindowManager::RegisterWindow(Window* window)
{
	if (!ListStart)
	{
		ListStart = window;
		ListStart->Next = 0;
		ListStart->Previous = 0;
		ListEnd = ListStart;
	}
	else
	{
		// Window gets focus, so add to the beginning of the window list
		window->Next =  ListStart;
		window->Next->Previous = window;
		window->Previous = NULL;
		ListStart = window;
	}
}

Image* WindowManager::InitTopbar(int width, char * text)
{
	int index = 0;
	Image* topbar =  Core::Gui->CreateImage(width, wnd_img_left->Height);
	Image* tmp = 0;

	#ifdef WINDOW_TITLES 
		// Blit left part first
		Core::Gui->BlitImageToImage(0, 0, wnd_img_left->Width, wnd_img_left->Height, wnd_img_left, 0, 0, topbar);
		index += wnd_img_left->Width;
	
	
		// Blit scaling part for text
		tmp = Core::Gui->ResizeImage((strlen(text)*6)+titlebartextoffsetx, wnd_img_scale_left->Height, wnd_img_scale_left);
		Core::Gui->BlitImageToImage(0, 0, tmp->Width, tmp->Height, tmp, index, 0, topbar);
		index += tmp->Width;
		Core::Gui->FreeImage(tmp);
	
	
		// Blit center part
		Core::Gui->BlitImageToImage(0, 0, wnd_img_center->Width, wnd_img_center->Height, wnd_img_center, index, 0, topbar);
		index += wnd_img_center->Width;
	#endif
	
	// Blit scaling right part
	tmp = Core::Gui->ResizeImage(width - index - wnd_img_right->Width, wnd_img_scale_right->Height, wnd_img_scale_right);
	Core::Gui->BlitImageToImage(0, 0, tmp->Width, tmp->Height, tmp, index, 0, topbar);
	index += tmp->Width;
	Core::Gui->FreeImage(tmp);
	
	// Blit last part
	Core::Gui->BlitImageToImage(0, 0, wnd_img_right->Width, wnd_img_right->Height, wnd_img_right, index, 0, topbar);
	
	// Blit close button
	Core::Gui->BlitAlphaImageToImage(0, 0, wnd_btn_close->Width, wnd_btn_close->Height, wnd_btn_close, width - wnd_btn_close->Width - 3, 0, topbar);
	
	#ifdef WINDOW_TITLES
		// Print text
		Core::Fonts->PrintImage(text, titlebartextoffsetx, titlebartextoffsety, topbar, 0xFF00D2FF, 0, 0);
	#endif
	return topbar;
}

Window* WindowManager::CreateWindow(WindowApp* application, char * name, int transparent, int fullscreen, int borders)
{
	Window* w = new Window();
	w->Fullscreen = fullscreen;
	w->Borders = borders;
	w->Topbar = InitTopbar(application->Width+2, name);
	w->Width = application->Width;
	w->Height = application->Height + w->Topbar->Height;
	w->X = createdLastX;
	w->Y = createdLastY;
	w->ContentX = w->X;
	w->ContentY = w->Y + w->Topbar->Height;
	w->Application = application;
	w->Transparent = transparent;
	w->Fullscreen = fullscreen;
	w->Borders = borders;
	w->Enabled = 1;

	RegisterWindow(w);
	createdLastX += 20;
	createdLastY += 10;
	return w;
}

void WindowManager::Focus(Window* window)
{
	Window* t = ListStart;
	
	if (window != t)
	{
		Window* cur = NULL;
		Window* prev= NULL;
		
		while (t && t->Next)
		{
			if (t->Next == window)
			{
				cur = t->Next;
				prev = t;
				break;
			}
			t = t->Next;
		}
		// if we are at the end of the list and there is a previous node set that node to be the end 
		if (cur == ListEnd && prev)
			ListEnd = prev;
		// set the next node of our previous node to our next
		prev->Next = cur->Next;
		// set the previous of our next node to our previous if there was any
		if (cur->Next)
			cur->Next->Previous = prev;
		// set our next node the to the original start of the list
		cur->Next = ListStart;
		// we are the first now, so we don't have a previous
		cur->Previous = NULL;
		// swap the previous node of our next node to our previous so we get rendered ;)
		cur->Next->Previous = cur;
		// set us to the static startnode
		ListStart = cur;
		// pfew.. done
	}
}

void WindowManager::WindowPosition(Window* window, int x, int y)
{
	if (!window->Borders)
		y -= window->Topbar->Height;
	window->X = x;
	window->Y = y;
	window->ContentX = x;
	window->ContentY = y + window->Topbar->Height;
}

void WindowManager::HandleFocus()
{
	if (Core::Ctrl->LastInput == PSP_CTRL_CROSS && ListStart && !IsBeingDragged)
	{
		Window* t = ListStart;
		while (t)
		{
			if (t->Enabled)
			{
				if (Interface::IsWithinWindow(Core::Ctrl->AnalogX, Core::Ctrl->AnalogY, t))
				{
					if (ListStart != t)
					{
						Focus(t);
						IsActive = 1;
						Core::Ctrl->Handled = 1;
					}
					break;
				}
				else if (Core::Ctrl->AnalogX < t->X || Core::Ctrl->AnalogY < t->Y || Core::Ctrl->AnalogX > (t->X + t->Width) || Core::Ctrl->AnalogY > (t->Y + t->Height))
					IsActive = 0;
			}
			t = t->Next;
		}
	}
}

void WindowManager::HandleDrag()
{
	if (Core::Ctrl->LastInput == PSP_CTRL_CROSS && ListStart && Core::Ctrl->AnalogX > ListStart->X + ListStart->Width - (wnd_btn_close->Width + 3) && Core::Ctrl->AnalogY > ListStart->Y && Core::Ctrl->AnalogX < (ListStart->X + ListStart->Width) && Core::Ctrl->AnalogY < (ListStart->Y + ListStart->Topbar->Height))
	{
				DestroyWindow(ListStart);
				Core::Ctrl->Handled = 1;
	}
	if (Core::Ctrl->LastInput == PSP_CTRL_CROSS && ListStart)
	{
		if (Interface::IsWithinImage(Core::Ctrl->AnalogX, Core::Ctrl->AnalogY, ListStart->X, ListStart->Y, ListStart->Topbar))
		{
			WindowPosition(ListStart, ListStart->X + (Core::Ctrl->AnalogX - Core::Ctrl->PreviousAnalogX), ListStart->Y + (Core::Ctrl->AnalogY - Core::Ctrl->PreviousAnalogY));
			IsBeingDragged = 1;
			Core::Ctrl->Handled = 1;
			IsActive = 1;
		}
		else if (Core::Ctrl->IsLastInputPressed && Core::Ctrl->LastInput == PSP_CTRL_CROSS && ListStart && IsBeingDragged)
		{
			WindowPosition(ListStart, ListStart->X + (Core::Ctrl->AnalogX - Core::Ctrl->PreviousAnalogX), ListStart->Y + (Core::Ctrl->AnalogY - Core::Ctrl->PreviousAnalogY));
			Core::Ctrl->Handled = 1;
			IsActive = 1;
		}
	}
	else if (IsBeingDragged)
		IsBeingDragged = 0;
}

void WindowManager::HandleController()
{
	if (ListStart)
	{
		if ((Interface::IsWithinWindowContent(Core::Ctrl->AnalogX, Core::Ctrl->AnalogY, ListStart) || IsActive) && ListStart->Enabled == 1)
		{
			if (!ListStart->Fullscreen)
				ListStart->HandleController(Core::Ctrl->AnalogX - ListStart->ContentX, Core::Ctrl->AnalogY - ListStart->ContentY, Core::Ctrl->LastInput);
			else
				ListStart->HandleController(Core::Ctrl->AnalogX, Core::Ctrl->AnalogY, Core::Ctrl->LastInput);
			Core::Ctrl->Handled = 1;
			IsActive = 1;
		}
		else
			IsActive = 0;
	}
}

void WindowManager::Handle()
{
	if (!Core::Ctrl->Handled)
	{
		HandleFocus();
		if (!Core::Ctrl->Handled)
			HandleDrag();
		if (!Core::Ctrl->Handled)
			HandleController();
	}
}

void WindowManager::Render()
{
	FullScreenEnabled = 0;
	if (ListEnd)
	{
		int width, height, offsetx, offsety, posx, posy;
		Window* t = ListEnd;
		while (t)
		{
			if (t->Enabled == 1)
			{
				t->Render();
				if (t->Fullscreen)
				{
					t->RenderFullscreen();
					t = t->Previous;
					FullScreenEnabled = 1;
					continue;
				}
				if (!(t->ContentY >= 272) && !(t->ContentX >= 480))
				{
				width = 0; height = 0; offsetx = 0; offsety = 0, posx = t->ContentX, posy = t->ContentY;
				// render window content
				// calculate size to render
				if (t->Application->Screen->Width + t->ContentX > 480)
					width = t->Application->Screen->Width - ((t->Application->Screen->Width + t->ContentX) - 480);
				if (t->X < 0)
				{
					width = t->Application->Screen->Width + t->ContentX;
					offsetx = -t->X;
					posx = 0;
				}
				if (t->Application->Screen->Height + t->ContentY > 272)
					height = t->Application->Screen->Height - ((t->Application->Screen->Height + t->ContentY) - 272);
				if (t->ContentY < 0)
				{
					height = t->Application->Screen->Height + t->ContentY;
					offsety = -t->ContentY;
					posy = 0;
				}
				// render the window content
				if (t->Transparent)
					Core::Gui->BlitAlphaImageToScreen(0, 0, t->Application->Screen->Width, t->Application->Screen->Height, t->Application->Screen, t->ContentX, t->ContentY);
				else {
				if (width && height)
					Core::Gui->BlitImageToScreen(offsetx, offsety, width, height, t->Application->Screen, posx, posy);
				if (width && !height)
					Core::Gui->BlitImageToScreen(offsetx, offsety, width, t->Application->Screen->Height, t->Application->Screen, posx, posy);
				if (!width && height)
					Core::Gui->BlitImageToScreen(offsetx, offsety, t->Application->Screen->Width, height, t->Application->Screen, posx, posy);
				if (!width && !height)
					Core::Gui->BlitImageToScreen(offsetx, offsety, t->Application->Screen->Width, t->Application->Screen->Height, t->Application->Screen, posx, posy); }
				
				if (t->Borders)
				{
					// render topbar
					Core::Gui->BlitAlphaImageToScreen(0, 0, t->Topbar->Width, t->Topbar->Height, t->Topbar, t->X, t->Y);
					// render shadows
					Core::Gui->BlitAlphaImageToScreen(0,0 , shadow_v_r->Width, t->Height, shadow_v_r, t->ContentX + t->Width, t->Y);
					Core::Gui->BlitAlphaImageToScreen(0,0 , shadow_v_l->Width, t->Height, shadow_v_l, t->ContentX - shadow_v_l->Width, t->Y);
					Core::Gui->BlitAlphaImageToScreen(0,0 , t->Width, shadow_h->Height, shadow_h, t->ContentX, t->Y + t->Height);
					Core::Gui->BlitAlphaImageToScreen(0,0 , shadow_c_r->Width, shadow_c_r->Height, shadow_c_r, t->ContentX + t->Width, t->Y + t->Height);
					Core::Gui->BlitAlphaImageToScreen(0,0 , shadow_c_l->Width, shadow_c_l->Height, shadow_c_l, t->ContentX - shadow_c_l->Width, t->Y + t->Height);
					}
				}
			}
			t = t->Previous;
		}
	}
}
