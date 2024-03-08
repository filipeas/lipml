typedef struct Image{
    int width;
    int height;
    std::vector<unsigned char>  image;
}Image;

// function for load image
Image *loadImage(const char* filename);
// function for apply average filter
Image *averageFilter(Image *image);
// function for apply mediam filter
Image *medianFilter(Image *image);
