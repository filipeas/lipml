#include "../standard/definitions.h"

typedef struct ift_image {
    int *val; // Brightness pixels array
    unsigned short *Cb; // Blue component pixels array
    unsigned short *Cr; // Red component pixels array
    unsigned short *alpha; // alpha component pixels array

    /** X axis size. */
    int xsize; // 
    /** Y axis size. */
    int ysize; // 
    /** Z axis size. */
    int zsize; // 

    int n; // number of pixels
} iftImage;

iftImage *iftCreateImageFromImage(iftImage *src);
iftImage  *iftCreateImageFromBuffer(int xsize,int ysize,int zsize, int *val);
static inline bool iftIsColorImage(iftImage *img) {
    return ((img->Cb != NULL) && (img->Cr != NULL));
}
iftImage *iftCreateImage(int xsize, int ysize, int zsize);
iftImage *iftCreateColorImage(int xsize, int ysize, int zsize, int depth);
uchar iftImageDepth(iftImage* img);
void iftMinMaxValues(iftImage *img, int *min, int *max);
void iftSetCbCr(iftImage *img, ushort value);
void  iftSetCbCrAlpha(iftImage *img, ushort value);
static inline long iftMaxImageRange(uchar img_depth) {
    return (1L << (img_depth)) - 1; // 2^img_depth -1
}