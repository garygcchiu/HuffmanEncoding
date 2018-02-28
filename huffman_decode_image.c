#include "huffman_decode_image.h"

struct PGM_Image *huffman_decode_image(int image_width, int image_height, 
	int max_gray_value, int number_of_nodes, struct node *huffman_node, 
	long int length_of_encoded_image, unsigned char *encoded_image){

	// need to build the huffman tree from the huffman nodes

	// begin decoding

	// for h from 0 to height
	// for w from 0 to width

		// always take the next bit and follow the tree until you reach a leaf,
		// at which point you know what the value of the pixel is at this position

		// restart from the root

	printf("NOT IMPLEMENTED\n");
	return NULL;
}
