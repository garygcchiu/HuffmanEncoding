#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libpnm.h"
#include "generate_huffman_nodes.h"

#ifndef _STORE_HUFFMAN_ENCODED_DATA_
#define _STORE_HUFFMAN_ENCODED_DATA_

void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, 
	int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, 
	long int length_of_encoded_image, unsigned char *encoded_image);

#endif