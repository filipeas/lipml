typedef struct ift_image {
    int *val; // Brightness pixels array
    ushort *Cb; // Blue component pixels array
    ushort *Cr; // Red component pixels array
    ushort *alpha; // alpha component pixels array

    int xsize; // X axis size
    int ysize; // Y axis size
    int zsize; // Z axis size

    int n; // Number of pixels
} iftImage;