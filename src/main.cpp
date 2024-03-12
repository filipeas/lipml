#include <iostream>
#include <vector>
#include <tuple>
#include "proto-image.h"

using namespace std;

int main(){
    // const char* filename = "./images/morfology.png";
    const char* filename = "./images/dog.png";

    // loading image
    Image *image = loadImage(filename);

    // convert to gray scale
    // Image *gray = convertToGrayscale(image);

    // check dimensions
    cout << "Image width: " << image->width << endl;
    cout << "Image height: " << image->height << endl;
    cout << "Image channels: " << image->channels << endl;

    // creating new image
    // Image *new_image = createImage(image->width, image->height);

    // saving image
    // saveImage(convertToGrayscale(image), "nova_imagem.png"); // salvando imagem em tons de cinza
    // saveImage(image, "nova_imagem.png"); // salvando imagem colorida

    // creating vectors
    std::vector<std::vector<int> > kernel_row = rowKernel(9, 1);
    std::vector<std::vector<int> > kernel_col = colKernel(3, 1);
    std::vector<std::vector<int> > kernel_square = squareKernel(3, 1);
    std::vector<std::vector<int> > kernel_rectangular = rectangularKernel(6, 3, 1);
    std::vector<std::vector<int> > kernel_circular = circularKernel(3, 1);

    // printing kernels
    // printMatrix(kernel_col);

    // dilation
    saveImage(dilation(image, kernel_square), "dilation.png");
    // erosion
    saveImage(erosion(image, kernel_square), "erosion.png");

    // destroy image
    destroyImage(image);

    return 0;
}
