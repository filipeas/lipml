# Library for Image Processing and Machine Learning (LIPML)

This Library had build for study during image processing and image analysis course in UNICAMP.

This project implement IFT algorithm (Image Foresting Transform) for make transformations in images. Below has a list with some manipulations into image using IFT.

IFT is an image processing technique used for image segmentation and analysis. It is used to find shortest paths in an image represented by a graph, where the pixels in the image are the nodes of the graph and the connections between the pixels are the edges.

The algorithm works by creating a forest of shortest paths in the image, where each tree represents a set of connected pixels that share similar characteristics. It then expands this forest, adding pixels as it calculates the shortest paths between pixels in the image.

[The paper of IFT is here.](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=343cb0ace2e88a237eb76db382c228bfcbaa053e)

## Dependences
- None

## How to compile c++
- First, make shure you have c++ compile in your machine.
- Execute ``` make ``` on terminal.

## Functions
- [IFT Algorithm](https://github.com/filipeas/lipml/tree/master/pseudocodes.md?tab=readme-ov-file#ift)
- Dynamic adjacency relation
- Some Data Structures:
    - linked list
    - circular list
    - bucket list