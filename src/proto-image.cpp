#include "proto-image.h"
#include <mm_malloc.h>

#include <iostream>
#include <string>

#include "lodepng.h"

Image *createImage(int width, int height){
    Image *proto_image = new Image();

    std::vector<unsigned char> image;
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

void destroyImage(Image *image) {
    if (image != NULL) {
        free(image->image.data()); // Liberando o vetor de bytes da imagem
        free(image); // Liberando a estrutura Image
    }
}

/**
 * Function always load RGBA image, i.e. load image with 4 channels
*/
Image *loadImage(const char* filename){
    Image *proto_image = new Image();

    std::vector<unsigned char> image;
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, filename);
    if(error) {
        std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        destroyImage(proto_image);
    }

    proto_image->width = width;
    proto_image->height = height;
    proto_image->image = image;
    proto_image->channels = image.size() / (width * height);

    return proto_image;
}

/**
 * Function convert image with C channels to image with 1 channel
*/
Image *convertToGrayscale(Image *image) {
    Image *proto_image = new Image();

    std::vector<unsigned char> grayscaleImage;
    grayscaleImage.reserve(image->width * image->height); // Reservar espaço para a imagem em escala de cinza

    // Loop através de cada pixel da imagem
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            int sum = 0;
            // Calcular a média dos canais de cor para obter o valor em escala de cinza
            for (int c = 0; c < image->channels; c++) {
                sum += image->image[image->channels * (i * image->width + j) + c];
            }
            char grayscaleValue = sum / image->channels; // Média dos valores dos canais
            grayscaleImage.push_back(grayscaleValue);
        }
    }

    proto_image->width = image->width;
    proto_image->height = image->height;
    proto_image->image = grayscaleImage;
    proto_image->channels = grayscaleImage.size() / (image->width * image->height);

    return proto_image;
}

int saveImage(Image *image, const char* filename){
    if(image->channels > 1){
        unsigned encode_error = lodepng::encode(filename, image->image, image->width, image->height);
        if (encode_error) {
            std::cerr << "encoder error " << encode_error << ": " << lodepng_error_text(encode_error) << std::endl;
            return 1;
        }
    } else{
        unsigned encode_error = lodepng::encode(filename, image->image, image->width, image->height, LCT_GREY);
        if (encode_error) {
            std::cerr << "encoder error " << encode_error << ": " << lodepng_error_text(encode_error) << std::endl;
            return 1;
        }
    }
    
    std::cout << "Blank image saved successfully." << std::endl;
    
    return 0;
}

std::vector<std::vector<int> > rowKernel(int size, int start){
    std::vector<std::vector<int> > kernel(1, std::vector<int>(size, start));
    return kernel;
}

std::vector<std::vector<int> > colKernel(int size, int start){
    std::vector<std::vector<int> > kernel(size, std::vector<int>(1, start));
    return kernel;
}

std::vector<std::vector<int> > squareKernel(int size, int start){
    std::vector<std::vector<int> > kernel(size, std::vector<int>(size, start));
    return kernel;
}

std::vector<std::vector<int> > rectangularKernel(int width, int height, int start){
    std::vector<std::vector<int> > kernel(height, std::vector<int>(width, start));
    return kernel;
}

std::vector<std::vector<int> > circularKernel(int radius, int start){
    int diameter = 2 * radius + 1;
    std::vector<std::vector<int> > kernel(diameter, std::vector<int>(diameter, 0));

    for (int i = 0; i < diameter; i++) {
        for (int j = 0; j < diameter; j++) {
            int distance = (i - radius) * (i - radius) + (j - radius) * (j - radius);
            if (distance <= radius * radius) {
                kernel[i][j] = start;
            }
        }
    }

    return kernel;
}

void printMatrix(const std::vector<std::vector<int> > &matrix){
    for (size_t i = 0; matrix.size(); i++){
        for (size_t j = 0; j < matrix[i].size(); j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Image *dilation(Image *image, std::vector<std::vector<int> > &kernel){
    Image *proto_image = new Image();

    // Converter a imagem em uma matriz 2D de inteiros
    std::vector<std::vector<int> > image2d(image->height, std::vector<int>(image->width));
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            image2d[i][j] = image->image[4 * image->width * i + 4 * j];
        }
    }

    int rows = image2d.size();
    int cols = image2d[0].size();
    int kRows = kernel.size();
    int kCols = kernel[0].size();

    // init a 2d matrix with 0s
    std::vector<std::vector<int> > result(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sum = 0;
            for (int m = 0; m < kRows; m++) {
                for (int n = 0; n < kCols; n++) {
                    int ii = i - kRows / 2 + m;
                    int jj = j - kCols / 2 + n;
                    if (ii >= 0 && ii < rows && jj >= 0 && jj < cols) {
                        sum += image2d[ii][jj] * kernel[m][n];
                    }
                }
            }
            result[i][j] = sum;
        }
    }

    // convertendo matriz 2d para imagem
    unsigned width = result[0].size();
    unsigned height = result.size();

    std::vector<unsigned char> png_image(width * height * 4); // Cada pixel tem 4 canais: RGBA

    // Preenchendo o vetor de bytes da imagem
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            unsigned char pixelValue = static_cast<unsigned char>(result[y][x]);
            png_image[4 * width * y + 4 * x] = pixelValue; // R
            png_image[4 * width * y + 4 * x + 1] = pixelValue; // G
            png_image[4 * width * y + 4 * x + 2] = pixelValue; // B
            png_image[4 * width * y + 4 * x + 3] = 255; // A (transparência completa)
        }
    }

    proto_image->width = image->width;
    proto_image->height = image->height;
    proto_image->image = png_image;
    proto_image->channels = image->image.size() / (image->width * image->height);

    return proto_image;
}

Image *erosion(Image *image, std::vector<std::vector<int> > &kernel){
    Image *proto_image = new Image();

    // Converter a imagem em uma matriz 2D de inteiros
    std::vector<std::vector<int> > image2d(image->height, std::vector<int>(image->width));
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            image2d[i][j] = image->image[4 * image->width * i + 4 * j];
        }
    }

    int rows = image2d.size();
    int cols = image2d[0].size();
    int kRows = kernel.size();
    int kCols = kernel[0].size();

    // init a 2d matrix with 0s
    std::vector<std::vector<int> > result(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int minVal = 255; // inicializa com o valor maximo
            for (int m = 0; m < kRows; m++) {
                for (int n = 0; n < kCols; n++) {
                    int ii = i - kRows / 2 + m;
                    int jj = j - kCols / 2 + n;
                    if (ii >= 0 && ii < rows && jj >= 0 && jj < cols) {
                        minVal = std::min(minVal, image2d[ii][jj] + kernel[m][n]);
                    }
                }
            }
            result[i][j] = minVal;
        }
    }

    // convertendo matriz 2d para imagem
    unsigned width = result[0].size();
    unsigned height = result.size();

    std::vector<unsigned char> png_image(width * height * 4); // Cada pixel tem 4 canais: RGBA

    // Preenchendo o vetor de bytes da imagem
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            unsigned char pixelValue = static_cast<unsigned char>(result[y][x]);
            png_image[4 * width * y + 4 * x] = pixelValue; // R
            png_image[4 * width * y + 4 * x + 1] = pixelValue; // G
            png_image[4 * width * y + 4 * x + 2] = pixelValue; // B
            png_image[4 * width * y + 4 * x + 3] = 255; // A (transparência completa)
        }
    }

    proto_image->width = image->width;
    proto_image->height = image->height;
    proto_image->image = png_image;
    proto_image->channels = image->image.size() / (image->width * image->height);

    return proto_image;
}
