/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: Image
# Desciption:
# Represents an Image entity that can be blitted to the screen. It is
# possible to blit to the image and perform several transformations to
# it.
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "../framework.h"

class Image{
	public:
		Image(int width, int height);
		~Image();
		void Clear(Color color);
		void Resize(int width, int height);
		void BlitImage(int sx, int sy, int width, int height, Image* image, int dx, int dy);
		void BlitAlphaImage(int sx, int sy, int width, int height, Image* source, int dx, int dy);
		Color* RawData();
	
	public:
		int Width;
		int Height;
		int TextureWidth;
		int TextureHeight;
		Color* Data;
	
	protected:
		unsigned long AlphaBlend(unsigned long front, unsigned long back);
		int GetNextPower2(int width);
	
};

#endif
