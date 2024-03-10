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
            if (image->image[4 * (y * image->width + x)] == 0) { // Se o pixel atual é preto
                // Verifica a vizinhança do pixel atual
                for (int ky = -kernel; ky <= kernel; ky++) {
                    for (int kx = -kernel; kx <= kernel; kx++) {
                        // Se algum vizinho do pixel atual é branco, então dilata
                        if (image->image[4 * ((y + ky) * image->width + (x + kx))] == 255) {
                            dilatedImage[4 * (y * image->width + x) + 0] = 255;
                            dilatedImage[4 * (y * image->width + x) + 1] = 255;
                            dilatedImage[4 * (y * image->width + x) + 2] = 255;
                            dilatedImage[4 * (y * image->width + x) + 3] = 255;
                            break; // Saia do loop interior, pois o pixel já foi dilatado
                        }
                    }
                    if (dilatedImage[4 * (y * image->width + x)] == 255) // Se o pixel foi dilatado, saia do loop exterior
                        break;
                }
            }
        }
    }

    proto_image->width = image->width;
    proto_image->height = image->height;
    proto_image->image = dilatedImage;

    return proto_image;
}
