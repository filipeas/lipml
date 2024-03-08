#include <iostream>
#include <vector>

#include <mm_malloc.h>
#include <ctype.h>
#include <string.h>

#include "lodepng.h"
#include "proto-image.h"

using namespace std;

int main(){
    const char* filename = "./images/dog.png";
    Image *image = loadImage(filename);

    cout << "Image width: " << image->width << endl;
    cout << "Image height: " << image->height << endl;
    
    return 0;
}

Image *loadImage(const char* filename){
    Image *proto_image = (Image *) malloc(sizeof(Image));

    vector<unsigned char> image;
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, filename);
    if(error) {
        cerr << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
    }

    proto_image->width = width;
    proto_image->height = height;
    proto_image->image = image;

    return proto_image;
}
