#include <iostream>

#include "proto-image.h"

using namespace std;

int main(){
    const char* filename = "./images/morfology.png";
    // const char* filename = "./images/dog.png";

    // loading image
    Image *image = loadImage(filename);

    // convert to gray scale
    Image *gray = convertToGrayscale(image);

    // check dimensions
    cout << "Image width: " << gray->width << endl;
    cout << "Image height: " << gray->height << endl;
    cout << "Image channels: " << gray->channels << endl;

    // creating new image
    // Image *new_image = createImage(image->width, image->height);

    // saving image
    // saveImage(convertToGrayscale(image), "nova_imagem.png"); // salvando imagem em tons de cinza
    // saveImage(image, "nova_imagem.png"); // salvando imagem colorida

    // dilation
    saveImage(dilation(image, 10), "dilation.png");
    // erosion
    saveImage(erosion(image, 10), "erosion.png");

    return 0;
}
