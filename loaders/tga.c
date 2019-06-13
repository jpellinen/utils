#include "tga.h"
#include <stdlib.h>
#include <string.h>

struct tga_t {
	unsigned int width;
	unsigned int height;
<<<<<<< HEAD
	unsigned int numComps;

	unsigned char *pixels;
=======
  unsigned int numComps;
    
  unsigned char *pixels;
>>>>>>> 14f0235... Fixed tabs in tga.c
};

typedef struct TGAHeader {
	unsigned char IDLength;
	unsigned char colorMapType;
	unsigned char imageType;
	unsigned char colorMapSpecs[5];
	
	// image specification.
	unsigned short originX;
	unsigned short originY;
	unsigned short width;
	unsigned short height;
	unsigned char pixelDepth;
	unsigned char imageDesc;
} TGAHeader;

static const unsigned int TRUE_COLOR = 2;
static const unsigned int TRUE_COLOR_RLE = 10;

tga_t *tga_load(const void *bytes)
{
	// header.
	const TGAHeader *header = (TGAHeader *)bytes;
		
	// supported types.
	if (header->imageType != TRUE_COLOR && header->imageType != TRUE_COLOR_RLE)
		return 0;
	// supported pixel depths.
	if (header->pixelDepth != 24 && header->pixelDepth != 32)
		return 0;
	// no color map.
	if (memcmp(header->colorMapSpecs, "\0\0\0\0\0", 5) != 0)
		return 0;
	
	// read image data.
<<<<<<< HEAD
	tga_t *tga = malloc(sizeof(tga_t));
	tga->width = (unsigned int)header->width;
=======
  tga_t *tga = malloc(sizeof(tga_t));
  tga->width = (unsigned int)header->width;
>>>>>>> 14f0235... Fixed tabs in tga.c
	tga->height = header->height;
	tga->numComps = header->pixelDepth / 8;

	tga->pixels = malloc(tga->width*tga->height*tga->numComps);
	const unsigned char *imageData = (unsigned char *)&bytes[sizeof(TGAHeader) + header->IDLength];
		
	int rle = 0;
	unsigned int repeat = 1;
	unsigned char r = 0, g = 0, b = 0, a = 0;

	for (unsigned int i = 0; i < tga->width*tga->height; ++i)
	{
		// read RLE-compression field.
		int newColor = 0;
		if (header->imageType == TRUE_COLOR_RLE && --repeat == 0)
		{
			unsigned char repetition = *(imageData++);
			rle = (repetition & 128) != 0;
			repeat = (repetition & 127) + 1;
			newColor = 1;
		}
		// read color components.
		if (!rle || newColor)
		{
			b = *(imageData++);
			g = *(imageData++);
			r = *(imageData++);
			a = (tga->numComps == 4) ? *(imageData++) : 0;
		}
		// store pixel.
		unsigned int x = i % tga->width;
		unsigned int y = i / tga->width;
		unsigned int index = (x + ((header->imageDesc & 32) ? y : tga->height-y-1) * tga->width)*tga->numComps;
		tga->pixels[index]   = r;
		tga->pixels[index+1] = g;
		tga->pixels[index+2] = b;
		if (tga->numComps == 4)
			tga->pixels[index+3] = a;
	}
	return tga;
}

void tga_release(tga_t *tga)
{
<<<<<<< HEAD
	free(tga->pixels);
	free(tga);
=======
  free(tga->pixels);
  free(tga);
>>>>>>> 14f0235... Fixed tabs in tga.c
}

unsigned int tga_getWidth(tga_t *tga)
{
<<<<<<< HEAD
	return tga->width;
=======
  return tga->width;
>>>>>>> 14f0235... Fixed tabs in tga.c
}

unsigned int tga_getHeight(tga_t *tga)
{
<<<<<<< HEAD
	return tga->height;
=======
  return tga->height;
>>>>>>> 14f0235... Fixed tabs in tga.c
}

unsigned int tga_getNumComps(tga_t *tga)
{
<<<<<<< HEAD
	return tga->numComps;
=======
  return tga->numComps;
>>>>>>> 14f0235... Fixed tabs in tga.c
}

unsigned char *tga_getPixels(tga_t *tga)
{
<<<<<<< HEAD
	return tga->pixels;
=======
  return tga->pixels;
>>>>>>> 14f0235... Fixed tabs in tga.c
}
