#include "huffman_decode_image.h"

struct PGM_Image *huffman_decode_image(int image_width, int image_height, 
	int max_gray_value, int number_of_nodes, struct node *huffman_node, 
	long int length_of_encoded_image, unsigned char *encoded_image){

	// Creating tree nodes and initializing values to -1 (to know which values have not been used)
	struct tree_node* root;
	struct tree_node** all_nodes = malloc(sizeof(struct tree_node) * (max_gray_value + 1));
	for(int i = 0; i < max_gray_value + 1; i++){
		all_nodes[i] = malloc(sizeof(struct tree_node));
		all_nodes[i]->value = -1;
	}

	int left_val;
	int right_val;
	struct tree_node* left;
	struct tree_node* right;
	struct tree_node* linker;
	for(int i = 0; i < number_of_nodes * 2; i += 2){
		/*
		* first_value is always added to the left (the 0 path)
		* second_value is always added to the right (the 1 path)
		*/

		// Getting the existing nodes
		left_val = huffman_node[i].first_value;
		right_val = huffman_node[i].second_value;

		left = all_nodes[left_val];
		right = all_nodes[right_val];

		// Setting leaf values if applicable
		if(left->value == -1){
			left->value = left_val;
		}
		if(right->value == -1){
			right->value = right_val;
		}

		// Making a node to link these two
		linker = malloc(sizeof(struct tree_node));
		linker->left = left;
		linker->right = right;
		linker->value = -2;

		// Setting it so on next iteration the linker will be targeted
		all_nodes[left_val] = linker;
		all_nodes[right_val] = linker;
	}
	root = linker;

	// Creating the image
	struct PGM_Image* image = malloc(sizeof(struct PGM_Image));
	create_PGM_Image(image, image_width, image_height, max_gray_value);

	// Variables needed for our position in the decoding
	int pos_in_encoding = 0;
	int cur_encoding = encoded_image[pos_in_encoding++];
	int pos_in_encoding_bit = 8;
	int direction;

	// Need a pixel value for each (x, y) coordinate
	for(int h = 0; h < image_height; h++){
		for(int w = 0; w < image_width; w++){
			struct tree_node* cur = root;

			// -2 denotes an internal node
			while(cur->value == -2){

				// use bitwise and to get current bit value
				direction = cur_encoding & pos_in_encoding_bit;

				// go the appropriate direction in the tree
				if(direction == 0){
					cur = cur->left;
				} else {
					cur = cur->right;
				}

				// shift bit to prepare for the next
				pos_in_encoding_bit = pos_in_encoding_bit >> 1;

				// if we are at 0 then we need the next encoded character, resest vars
				if(pos_in_encoding_bit == 0){
					cur_encoding = encoded_image[pos_in_encoding++];
					pos_in_encoding_bit = 8;
				} 
			}

			// we exit the while once we reach a leaf, so use this value in image
			image->image[h][w] = cur->value;
		}
	}
	free(all_nodes);
	free(left);
	free(right);
	free(linker);
	return image;
}
