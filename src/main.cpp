#include <iostream>

#include "proto-image.h"

using namespace std;

int main(){
    const char* filename = "./images/morfology.png";

    // loading image
    Image *image = loadImage(filename);

    // check dimensions
    cout << "Image width: " << image->width << endl;
    cout << "Image height: " << image->height << endl;

    // creating new image
    // Image *new_image = createImage(image->width, image->height);

    // saving image
    // saveImage(new_image, "nova_imagem.png");

    // dilation
    saveImage(dilation(image, 3), "dilation.png");

    return 0;
}
