// Juha Pellinen - 2011

#ifndef _TGA_H_
#define _TGA_H_

typedef struct tga_t tga_t;

#ifdef __cplusplus
extern "C" {
#endif

tga_t *tga_load(const void *bytes);
void tga_release(tga_t *tga);

unsigned int tga_getWidth(tga_t *tga);
unsigned int tga_getHeight(tga_t *tga);
unsigned int tga_getNumComps(tga_t *tga);
unsigned char *tga_getPixels(tga_t *tga);
    
#ifdef __cplusplus
}
#endif

#endif
