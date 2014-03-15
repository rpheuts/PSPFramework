#include <stdlib.h>
#include <pspdisplay.h>
#include <psputils.h>
#include <pspgu.h>
#include <string.h>
#include <png.h>
#include <pspiofilemgr.h>

extern "C" {
#include <jpeglib.h>
#include <jerror.h>
}

#include "../framework.h"

#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define SLICE_SIZE 32 // change this to experiment with different page-cache sizes


#ifndef png_jmpbuf
#  define png_jmpbuf(png_ptr) ((png_ptr)->jmpbuf)
#endif

Graphics::Graphics(int screenWidth, int screenHeight, int lineSize)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_screenLineSize = lineSize;
	_frameBufferSize = _screenLineSize*_screenHeight*4;
	_vramBase = (Color*) (0x40000000 | 0x04000000);
	
      	_screenBuffNum = 0;
      	sceDisplaySetMode(0, _screenWidth, _screenHeight);
	sceGuInit();

	// setup
	sceGuStart(GU_DIRECT,_gulist);
        sceGuDrawBuffer(GU_PSM_8888, (void*)_frameBufferSize, _screenLineSize);
        sceGuDispBuffer(_screenWidth, _screenHeight, (void*)0, _screenLineSize);
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
        sceGuDepthBuffer((void*) (_frameBufferSize*2), _screenLineSize);
        sceGuOffset(2048 - (_screenWidth / 2), 2048 - (_screenHeight / 2));
        sceGuViewport(2048, 2048, _screenWidth, _screenHeight);
        sceGuDepthRange(0xc350, 0x2710);
        sceGuScissor(0, 0, _screenWidth, _screenHeight);
        sceGuEnable(GU_SCISSOR_TEST);
        sceGuAlphaFunc(GU_GREATER, 0, 0xff);
        sceGuEnable(GU_ALPHA_TEST);
        sceGuDepthFunc(GU_GEQUAL);
        sceGuEnable(GU_DEPTH_TEST);
        sceGuFrontFace(GU_CW);
        sceGuShadeModel(GU_SMOOTH);
        sceGuEnable(GU_CULL_FACE);
        sceGuEnable(GU_TEXTURE_2D);
        sceGuEnable(GU_CLIP_PLANES);
        sceGuTexMode(GU_PSM_8888, 0, 0, 0);
        sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA); //new
	sceGuTexFilter(GU_LINEAR,GU_LINEAR);  //new 
        sceGuAmbientColor(0xffffffff);
        sceGuEnable(GU_BLEND);
        sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
        sceGuFinish();
      	sceGuSync(0, 0);

        sceDisplayWaitVblankStart();
        sceGuDisplay(GU_TRUE);
        Core::Dbg->Log(Init, "Graphics Library loaded...");
}

Color* Graphics::GetVramDrawBuffer()
{
	Color* vram = (Color*) _vramBase;
	if (_screenBuffNum == 0) vram += _frameBufferSize / sizeof(Color);
	return vram;
}

Color* Graphics::GetVramDisplayBuffer()
{
	Color* vram = (Color*) _vramBase;
	if (_screenBuffNum == 1) vram += _frameBufferSize / sizeof(Color);
	return vram;
}

Image* Graphics::Load(string filename)
{
	if (filename.find(".png") != string::npos)
		return LoadPNG(filename);
	else if (filename.find(".png") != string::npos)
		return LoadJPG(filename);
	return NULL;
}

Image* Graphics::CreateImage(int width, int height)
{
	return new Image(width, height);
}

void Graphics::FreeImage(Image* image)
{
	delete (image);
}

void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg)
{

}

Image* Graphics::LoadPNG(string filename)
{
        png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	png_uint_32 width, height, x, y;
	int bit_depth, color_type, interlace_type;
	u32* line;
	FILE *fp;

	if ((fp = fopen(filename.c_str(), "rb")) == NULL) return NULL;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fclose(fp);
		return NULL;
	}
	png_set_error_fn(png_ptr, (png_voidp) NULL, (png_error_ptr) NULL, user_warning_fn);
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, sig_read);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, int_p_NULL, int_p_NULL);
	
	Image* image = new Image(width, height);
	png_set_strip_16(png_ptr);
	png_set_packing(png_ptr);
	if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_gray_1_2_4_to_8(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);
	png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
	if (!image->Data) {
		delete(image);
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	line = (u32*) malloc(width * 4);
	if (!line) {
		delete(image);
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	for (y = 0; y < height; y++) {
		png_read_row(png_ptr, (u8*) line, png_bytep_NULL);
		for (x = 0; x < width; x++) {
			u32 color = line[x];
			image->Data[x + y * image->TextureWidth] =  color;
		}
	}
	free(line);
	// png_read_end(png_ptr, info_ptr);
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
	fclose(fp);
	return image;
}

Image* Graphics::LoadJPG(string filename)
{
        struct jpeg_decompress_struct dinfo;
        struct jpeg_error_mgr jerr;
        dinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&dinfo);
        FILE* inFile = fopen(filename.c_str(), "rb");
        if (!inFile) {
                jpeg_destroy_decompress(&dinfo);
                return NULL;
        }
        jpeg_stdio_src(&dinfo, inFile);
        jpeg_read_header(&dinfo, TRUE);
        int width = dinfo.image_width;
        int height = dinfo.image_height;
        jpeg_start_decompress(&dinfo);
        Image* image = new Image(width, height);
        if (!image) {
                jpeg_destroy_decompress(&dinfo);
                fclose(inFile);
                return NULL;
        }
        u8* line = (u8*) malloc(width * 3);
        if (!line) {
        	delete(image);
                jpeg_destroy_decompress(&dinfo);
                fclose(inFile);
                return NULL;
        }
        int x;
        if (dinfo.jpeg_color_space == JCS_GRAYSCALE) {
                while (dinfo.output_scanline < dinfo.output_height) {
                        int y = dinfo.output_scanline;
                        jpeg_read_scanlines(&dinfo, &line, 1);
                        for (x = 0; x < width; x++) {
                                Color c = line[x];
                                image->Data[x + image->TextureWidth * y] = c | (c << 8) | (c << 16) | 0xff000000;;
                        }
                }
        } else {
                while (dinfo.output_scanline < dinfo.output_height) {
                        int y = dinfo.output_scanline;
                        jpeg_read_scanlines(&dinfo, &line, 1);
                        u8* linePointer = line;
                        for (x = 0; x < width; x++) {
                                Color c = *(linePointer++);
                                c |= (*(linePointer++)) << 8;
                                c |= (*(linePointer++)) << 16;
                                image->Data[x + image->TextureWidth * y] = c | 0xff000000;
                        }
                }
        }
        jpeg_finish_decompress(&dinfo);
        jpeg_destroy_decompress(&dinfo);
        free(line);
        fclose(inFile);
        return image;
}

void Graphics::BlitImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy)
{
	Color* vram = GetVramDrawBuffer();
	sceKernelDcacheWritebackInvalidateAll();
	sceGuStart(GU_DIRECT,_gulist);
	sceGuTexMode(GU_PSM_8888,0,0,0);
	sceGuCopyImage(GU_PSM_8888, sx, sy, width, height, source->TextureWidth, source->Data, dx, dy, _screenLineSize, vram);
	sceGuFinish();
	sceGuSync(0,0);
}

void Graphics::BlitAlphaImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy)
{
        sceKernelDcacheWritebackInvalidateAll();
        sceGuStart(GU_DIRECT, _gulist);
        sceGuTexMode(GU_PSM_8888,0,0,0);
        sceGuTexImage(0, source->TextureWidth, source->TextureHeight, source->TextureWidth, (void*) source->Data);
        sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
		  sceGuTexFilter(GU_LINEAR,GU_LINEAR); 
        float u = 1.0f / ((float)source->TextureWidth);
        float v = 1.0f / ((float)source->TextureHeight);
        sceGuTexScale(u, v);
        
        int j = 0;
        while (j < width) {
                Vertex* vertices = (Vertex*) sceGuGetMemory(2 * sizeof(Vertex));
                int sliceWidth = 64;
                if (j + sliceWidth > width) sliceWidth = width - j;
                vertices[0].u = sx + j;
                vertices[0].v = sy;
                vertices[0].x = dx + j;
                vertices[0].y = dy;
                vertices[0].z = 0;
                vertices[1].u = sx + j + sliceWidth;
                vertices[1].v = sy + height;
                vertices[1].x = dx + j + sliceWidth;
                vertices[1].y = dy + height;
                vertices[1].z = 0;
                sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, vertices);
                j += sliceWidth;
        }
        
        sceGuFinish();
        sceGuSync(0, 0);
}

void Graphics::BlitImageToImage(int sx, int sy, int width, int height, Image* source, int dx, int dy, Image* destination)
{
	Color* dest = destination->RawData();
	sceKernelDcacheWritebackInvalidateAll();
	sceGuStart(GU_DIRECT,_gulist);
	sceGuTexMode(GU_PSM_8888,0,0,0);
	sceGuCopyImage(GU_PSM_8888, sx, sy, width, height, source->TextureWidth, source->Data, dx, dy, _screenLineSize, dest);
	sceGuFinish();
	sceGuSync(0,0);
}

void Graphics::BlitAlphaImageToImage(int sx, int sy, int width, int height, Image* source, int dx, int dy, Image* destination)
{
	Color* destinationData = &destination->RawData()[destination->TextureWidth * dy + dx];
	int destinationSkipX = destination->TextureWidth - width;
	Color* sourceData = &source->RawData()[source->TextureWidth * sy + sx];
	int sourceSkipX = source->TextureWidth - width;
	int x, y;
	for (y = 0; y < height; y++, destinationData += destinationSkipX, sourceData += sourceSkipX) {
		for (x = 0; x < width; x++, destinationData++, sourceData++) {
			Color color = *sourceData;
			if (!IS_ALPHA(color)) *destinationData = AlphaBlend(color, *destinationData);
		}
	}
}

Image* Graphics::ResizeImage(int width, int height, Image* source)
{
	if (source == NULL)
		return NULL;
		
	Image* destination = CreateImage(width, height);
	ResizeImage(width, height, source, destination);
	return destination;
}

void Graphics::ResizeImage(int width, int height, Image* source, Image* destination)
{
	if (source == NULL)
		return;
	Color* destinationData = destination->RawData();
	int destinationSkipX = destination->TextureWidth - width;
	Color* sourceData = source->RawData();
	float scaleFactorX = ((float)source->Width) / ((float)width);
	float scaleFactorY = ((float)source->Height) / ((float)height);
	
	int x, y;
	for (y = 0; y < height; y++, destinationData += destinationSkipX) {
		for (x = 0; x < width; x++, destinationData++) {
			*destinationData = sourceData[(int)((int)(scaleFactorY * y) * source->TextureWidth) + (int)(x * scaleFactorX)];
		}
	}
}

void Graphics::ClearImage(Color color, Image* image)
{
	int i;
	int size = image->TextureWidth * image->TextureHeight;
	Color* data = image->RawData();
	for (i = 0; i < size; i++, data++) *data = color;
}

Image* Graphics::GetDisplayBuffer()
{
	Image* image = new Image(_screenWidth, _screenHeight);
	
	Color* destinationData = &image->Data[0];
	int destinationSkipX = image->TextureWidth - _screenWidth;
	Color* sourceData = GetVramDisplayBuffer();
	int sourceSkipX = image->TextureWidth - _screenWidth;
	int x, y;
	for (y = 0; y < _screenHeight; y++, destinationData += destinationSkipX, sourceData += sourceSkipX) {
		for (x = 0; x < _screenWidth; x++, destinationData++, sourceData++) {
			*destinationData = *sourceData;
		}
	}
	return image;
}

void Graphics::FlipScreen()
{
	sceGuSwapBuffers();
   	_screenBuffNum ^= 1;
   
   	sceGuClearColor(0);
   	sceGuClear(GU_COLOR_BUFFER_BIT);
}


void Graphics::WaitVblankStart()
{
	sceDisplayWaitVblankStart();
}

void Graphics::ClearScreen(Color color)
{
	sceGuStart(GU_DIRECT, _gulist);
   	sceGuClearColor(0);
   	sceGuClear(GU_COLOR_BUFFER_BIT);
   	sceGuFinish();
   	sceGuSync(0,0); 
}

void Graphics::SavePNG(string filename, Image* image, int saveAlpha)
{
	SavePNG(filename, image->Data, image->Width, image->Height, saveAlpha);
}

void Graphics::SavePNG(string filename, Color* data, int width, int height, int saveAlpha)
{
        png_structp png_ptr;
        png_infop info_ptr;
        FILE* fp;
        int i, x, y;
        u8* line;
        
        if ((fp = fopen(filename.c_str(), "wb")) == NULL) return;
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr) return;
        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
                png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
                return;
        }
        png_init_io(png_ptr, fp);
        png_set_IHDR(png_ptr, info_ptr, width, height, 8,
                saveAlpha ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB,
                PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
        png_write_info(png_ptr, info_ptr);
        line = (u8*) malloc(width * (saveAlpha ? 4 : 3));
        for (y = 0; y < height; y++) {
                for (i = 0, x = 0; x < width; x++) {
                        Color color = data[x + y * _screenLineSize];
                        u8 r = color & 0xff; 
                        u8 g = (color >> 8) & 0xff;
                        u8 b = (color >> 16) & 0xff;
                        u8 a = saveAlpha ? (color >> 24) & 0xff : 0xff;
                        line[i++] = r;
                        line[i++] = g;
                        line[i++] = b;
                        if (saveAlpha) line[i++] = a;
                }
                png_write_row(png_ptr, line);
        }
        free(line);
        png_write_end(png_ptr, info_ptr);
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(fp);
}

void Graphics::Screenshot(string filename)
{
	SavePNG(filename, GetVramDisplayBuffer(), _screenWidth, _screenHeight, 0);
}

static SceUID fd = 0;
void user_read_data_fn(png_structp png_ptr, png_bytep data, png_size_t length)
{
   sceIoRead(fd, data, length);
}

Image* Graphics::StreamPNG(SceUID uid)
{
   png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	png_uint_32 width, height, x, y;
	int bit_depth, color_type, interlace_type;
	u32* line;
	fd = uid;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		return NULL;;
	}
	
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	
	png_set_read_fn(png_ptr, (png_voidp *)uid, user_read_data_fn); 
	png_set_error_fn(png_ptr, (png_voidp) NULL, (png_error_ptr) NULL, user_warning_fn);
	
	png_set_sig_bytes(png_ptr, sig_read);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, int_p_NULL, int_p_NULL);
	
	Image* image = new Image(width, height);
	png_set_strip_16(png_ptr);
	png_set_packing(png_ptr);
	if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_gray_1_2_4_to_8(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);
	png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
	if (!image->Data) {
		delete(image);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	line = (u32*) malloc(width * 4);
	if (!line) {
		delete(image);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	
	for (y = 0; y < height; y++) {
		png_read_row(png_ptr, (u8*) line, png_bytep_NULL);
		for (x = 0; x < width; x++) {
			u32 color = line[x];
			image->Data[x + y * image->TextureWidth] =  color;
		}
	}
	free(line);
	// png_read_end(png_ptr, info_ptr);
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
	return image;
}
