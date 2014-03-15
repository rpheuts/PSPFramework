#include <malloc.h>
#include "../framework.h"

Image::Image(int imageWidth, int imageHeight)
{
	Width = imageWidth;
	Height = imageHeight;
	
	// Set the texturewidth, needed for blitting
	TextureWidth = GetNextPower2(Width);
        TextureHeight = GetNextPower2(Height);
        
        // Init the raw data
        Data = (Color*) memalign(16, TextureWidth * TextureHeight * sizeof(Color));
        if (!Data) return;
        memset(Data, 0, TextureWidth * TextureHeight * sizeof(Color));
}

Image::~ Image()
{
	free (Data);
}

void Image::Clear(Color color)
{
	int i;
	int size = TextureWidth * TextureHeight;
	for (i = 0; i < size; i++, Data++) * Data = color;
}

Color* Image::RawData()
{
	return Data;
}

void Image::Resize(int newWidth, int newHeight)
{
	// Init destination and check source != null
	if (Data == NULL)
		return;
	int destTexWidth = GetNextPower2(newWidth);
	Color* destinationData = (Color*) memalign(16, destTexWidth * GetNextPower2(newHeight) * sizeof(Color));
	if (!destinationData) 
		return;
	 memset(destinationData, 0, destTexWidth * GetNextPower2(newHeight) * sizeof(Color));
	 
	// Calculate scaling factors
	int destinationSkipX = destTexWidth - Width;
	Color* sourceData = &Data[0];
	float scaleFactorX = ((float)Width) / ((float)newWidth);
	float scaleFactorY = ((float)Height) / ((float)newHeight);
	
	// Perform scaling
	int x, y;
	for (y = 0; y < Height; y++, destinationData += destinationSkipX) {
		for (x = 0; x < Width; x++, destinationData++) {
			*destinationData = sourceData[(int)((int)(scaleFactorY * y) * Width) + (int)(x * scaleFactorX)];
		}
	}
	
	// Free original and assign the new scaled image
	free(Data);
	Data = destinationData;
}


void Image::BlitImage(int sx, int sy, int sWidth, int sHeight, Image* source, int dx, int dy)
{
	Color* destinationData = &Data[TextureWidth * dy + dx];
	int destinationSkipX = TextureWidth - sWidth;
	Color* sourceData = &source->Data[source->TextureWidth * sy + sx];
	int sourceSkipX = source->TextureWidth - sWidth;
	int x, y;
	for (y = 0; y < sHeight; y++, destinationData += destinationSkipX, sourceData += sourceSkipX) {
		for (x = 0; x < sWidth; x++, destinationData++, sourceData++) {
			*destinationData = *sourceData;
		}
	}
}


void Image::BlitAlphaImage(int sx, int sy, int sWidth, int sHeight, Image* source, int dx, int dy)
{
	Color* destinationData = &Data[TextureWidth * dy + dx];
	int destinationSkipX = TextureWidth - sWidth;
	Color* sourceData = &source->Data[source->TextureWidth * sy + sx];
	int sourceSkipX = source->TextureWidth - sWidth;
	int x, y;
	for (y = 0; y < sHeight; y++, destinationData += destinationSkipX, sourceData += sourceSkipX) {
		for (x = 0; x < sWidth; x++, destinationData++, sourceData++) {
			Color color = *sourceData;
			if (!IS_ALPHA(color)) *destinationData = AlphaBlend(color, *destinationData);
		}
	}
}

unsigned long Image::AlphaBlend(unsigned long front, unsigned long back)
{
   unsigned short alpha = GET_ALPHA(front);
   unsigned short beta = 255 - alpha;

   return MK8888(
	   ((GET_BLUE(front) * alpha) + (GET_BLUE(back) * beta)) / 255,
       ((GET_GREEN(front) * alpha) + (GET_GREEN(back) * beta)) / 255,
       ((GET_RED(front) * alpha) + (GET_RED(back) * beta)) / 255,
	   (GET_ALPHA(back)));
}

// Used for calculating the actual texture width (power of 2) for blitting
int Image::GetNextPower2(int width)
{
	int b = width;
	int n;
	for (n = 0; b != 0; n++) b >>= 1;
	b = 1 << n;
	if (b == 2 * width) b >>= 1;
	return b;
}
