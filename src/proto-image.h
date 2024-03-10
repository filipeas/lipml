#include <vector>

typedef struct Image{
    int width;
    int height;
    int channels;
    std::vector<unsigned char> image;
}Image;

// function forr create image
Image *createImage(int width, int height);
// function for load image
Image *loadImage(const char* filename);
// function to convert image to gray scale
Image *convertToGrayscale(Image *image);
// function for save image
int saveImage(Image *image, const char* filename);

/**
 * Functions for operations
*/
Image *dilation(Image *image, int kernel);
Image *erosion(Image *image, int kernel);
// Image *opening(Image *image, int kernel);
// Image *closing(Image *image, int kernel);
