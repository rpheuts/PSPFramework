/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: Graphics
# Desciption:
# Provides interface and graphical functionality for blitting images
# and content to the screen. Uses the GU kernel functions for better
# performance.
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

//Typedefs
typedef struct
{
        unsigned short u, v;
        short x, y, z;
} Vertex;

typedef struct
{
	int x; 
	int y;
} Position;

class Graphics{
	public:
		Graphics(int screenWidth, int screenHeight, int lineSize);
		
		// Returns the current draw buffer
		Color* GetVramDrawBuffer();
		
		// Returns the current display buffer
		Color* GetVramDisplayBuffer();
		
		// Returns an emtpy image (DEPRICATED, please instantiate image class yourself)
		Image* CreateImage(int width, int height);
		
		// Frees an image from mem (DEPRICATED, please free image class yourself)
		void FreeImage(Image* image);
		
		// Load a JPG or PNG image (judged by the extension)
		Image* Load(string filename);
		
		// Load a PNG image
		Image* LoadPNG(string filename);
		
		// Load a JPG image
		Image* LoadJPG(string filename);
		
		// Can resize one image and blit it to another newly created image leaving the original untouched
		Image* ResizeImage(int width, int height, Image* source);
		
		// Can resize one image and blit it to another image leaving the original untouched
		void ResizeImage(int width, int height, Image* source, Image* destination);
		
		// Clears the image with the specified color
		void ClearImage(Color color, Image* image);
		
		// Returns the current display buffer as an Image
		Image* GetDisplayBuffer();
		
		// Sets the current draw buffer to the display buffer, and the current display buffer to the draw buffer
		void FlipScreen();
		
		// Wait for VSync (screen is fully drawn)
		void WaitVblankStart();
		
		// Blit an image to the screen at xd,dy with size width,height
		void BlitImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy);
		
		// Blit an image containing alpha data to the screen
		void BlitAlphaImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy);
		
		// Blit an image to another image at the specified postition with specified width and height
		void BlitImageToImage(int sx, int sy, int width, int height, Image* source, int dx, int dy, Image* destination);
		
		// Blit an image to another image at the specified postition with specified width and height with alphablending
		void BlitAlphaImageToImage(int sx, int sy, int width, int height, Image* source, int dx, int dy, Image* destination);
		
		// Clear the screen with a specific color
		void ClearScreen(Color color);
		
		// Save an Image to a PNG file
		void SavePNG(string filename, Image* image, int saveAlpha);
		
		// Save raw data to a PNG file
		void SavePNG(string filename, Color* data, int width, int height, int saveAlpha);
		
		// Take a screenshot of the current display and save it
		void Screenshot(string filename);
		
		// Can stream load a png from a open file with id 'uid'
		Image* StreamPNG(int uid);
		
		// Can alpha blend (using the CPU) two parts together
		inline unsigned long Graphics::AlphaBlend(unsigned long front, unsigned long back)
		{
			unsigned short alpha = GET_ALPHA(front);
			unsigned short beta = 255 - alpha;

			return MK8888(
				((GET_BLUE(front) * alpha) + (GET_BLUE(back) * beta)) / 255,
				((GET_GREEN(front) * alpha) + (GET_GREEN(back) * beta)) / 255,
				((GET_RED(front) * alpha) + (GET_RED(back) * beta)) / 255,
				(GET_ALPHA(back)));
		}
		
	private:
		int _screenWidth;
		int _screenHeight;
		int _screenLineSize;
		int _screenBuffNum;
		int _frameBufferSize;
		Color* _vramBase;
		unsigned int __attribute__((aligned(16))) _gulist[262144];
};
#endif
