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
std::vector<std::vector<int> > rowKernel(int size, int start);
std::vector<std::vector<int> > colKernel(int size, int start);
std::vector<std::vector<int> > squareKernel(int size, int start);
std::vector<std::vector<int> > rectangularKernel(int width, int height, int start);
std::vector<std::vector<int> > circularKernel(int radius, int start);
void printMatrix(const std::vector<std::vector<int> > &matrix);
Image *dilation(Image *image, std::vector<std::vector<int> > &kernel);
Image *erosion(Image *image, std::vector<std::vector<int> > &kernel);
// Image *opening(Image *image, int kernel);
// Image *closing(Image *image, int kernel);
