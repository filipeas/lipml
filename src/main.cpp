#include <iostream>
#include <vector>
#include <string>

#include <mm_malloc.h>
#include <ctype.h>

#include "lodepng.h"
#include "proto-image.h"

using namespace std;

int main(){
    const char* filename = "./images/dog.png";
    Image *image = loadImage(filename);

    cout << "Image width: " << image->width << endl;
    cout << "Image height: " << image->height << endl;

    // creating new image
    Image *new_image = createImage(image->width, image->height);

    // saving image
    saveImage(new_image, "nova_imagem.png");

    return 0;
}

Image *createImage(int width, int height){
    Image *proto_image = (Image *) malloc(sizeof(Image));

    vector<unsigned char> image;
    image.resize(width * height * 4); // 4 for RGBA (1 byte for band). Must be 4 because of bib lodepng, that receive 4 bytes for create image on RGBA format

    for(size_t i = 0; i < image.size(); i += 3){
        image[i + 0] = 0; // 0 for red
        image[i + 1] = 0; // 0 for green
        image[i + 2] = 0; // 0 for blue
        image[i + 3] = 255; // 0 for alpha
    }

    proto_image->width = width;
    proto_image->height = height;
    proto_image->image = image;

    return proto_image;
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

int saveImage(Image *image, const char* filename){
    unsigned encode_error = lodepng::encode(filename, image->image, image->width, image->height);
    if (encode_error) {
        std::cerr << "encoder error " << encode_error << ": " << lodepng_error_text(encode_error) << std::endl;
        return 1;
    } else {
        std::cout << "Blank image saved successfully." << std::endl;
    }

    return 0;
}
