#include <vector>

typedef struct Image{
    int width;
    int height;
    std::vector<unsigned char> image;
}Image;

// function forr create image
Image *createImage(int width, int height);
// function for load image
Image *loadImage(const char* filename);
// function for save image
int saveImage(Image *image, const char* filename);

/**
 * Functions for operations
*/
Image *dilation(Image *image, int kernel);
