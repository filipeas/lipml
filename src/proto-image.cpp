#include "proto-image.h"
#include <mm_malloc.h>

#include <iostream>
#include <string>

#include "lodepng.h"

Image *createImage(int width, int height){
    Image *proto_image = (Image *) malloc(sizeof(Image));

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

/**
 * Function always load RGBA image, i.e. load image with 4 channels
*/
Image *loadImage(const char* filename){
    Image *proto_image = (Image *) malloc(sizeof(Image));

    std::vector<unsigned char> image;
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, filename);
    if(error) {
        std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
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
    Image *proto_image = (Image *) malloc(sizeof(Image));

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

/**
 * image: an image
 * kernel: n * 3, with n > 0
*/
Image *dilation(Image *image, int kernel){
    if (kernel <= 0){
        std::cerr << "Size of kernel must be > 0." << std::endl;
        return image;
    }

    Image *proto_image = (Image *) malloc(sizeof(Image));

    std::vector<unsigned char> dilatedImage = image->image;

    // Percorre todos os pixels da imagem
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            // loop sobre os canais da imagem
            for (int c = 0; c < image->channels; c++){
                if (image->image[image->channels * (y * image->width + x) + c] == 0) { // Se o pixel atual é preto, considerando o acesso unidimensional da imagem (y é a largura, multiplicando pela largura da imagem e somando com o deslocamento x, é possivel acessar a posicao (x,y) de forma unidimensional)
                    // Verifica a vizinhança do pixel atual
                    for (int ky = -kernel; ky <= kernel; ky++) {
                        for (int kx = -kernel; kx <= kernel; kx++) {
                            // Se algum vizinho do pixel atual é branco, então dilata
                            if (image->image[image->channels * ((y + ky) * image->width + (x + kx)) + c] == 255) {
                                dilatedImage[image->channels * (y * image->width + x) + c] = 255;
                                break; // Saia do loop interior, pois o pixel já foi dilatado
                            }
                        }
                    }
                }
            }
        }
    }

    proto_image->width = image->width;
    proto_image->height = image->height;
    proto_image->image = dilatedImage;
    proto_image->channels = image->image.size() / (image->width * image->height);

    return proto_image;
}

/**
 * image: an image
 * kernel: n * 3, with n > 0
*/
Image *erosion(Image *image, int kernel){
    if (kernel <= 0){
        std::cerr << "Size of kernel must be > 0." << std::endl;
        return image;
    }

    Image *proto_image = (Image *) malloc(sizeof(Image));

    std::vector<unsigned char> erodedImage = image->image;

    // Percorre todos os pixels da imagem
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            // loop sobre os canais da imagem
            for (int c = 0; c < image->channels; c++){
                if (image->image[image->channels * (y * image->width + x) + c] == 255) { // Se o pixel atual é branco
                    bool erode = false;
                    // Verifica a vizinhança do pixel atual
                    for (int ky = -kernel; ky <= kernel; ky++) {
                        for (int kx = -kernel; kx <= kernel; kx++) {
                            // Se algum vizinho do pixel atual é preto, então não erode
                            if (image->image[image->channels * ((y + ky) * image->width + (x + kx)) + c] == 0) {
                                erode = true;
                                break;
                            }
                        }
                        if (erode) break;
                    }
                    if (erode) {
                        erodedImage[image->channels * (y * image->width + x) + 0] = 255; // R
                        erodedImage[image->channels * (y * image->width + x) + 1] = 255; // G
                        erodedImage[image->channels * (y * image->width + x) + 2] = 255; // B
                        erodedImage[image->channels * (y * image->width + x) + 3] = 255;
                    }
                }
            }
        }
    }

    proto_image->width = image->width;
    proto_image->height = image->height;
    proto_image->image = erodedImage;
    proto_image->channels = image->image.size() / (image->width * image->height);

    return proto_image;
}
