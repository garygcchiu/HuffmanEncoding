#include "store_huffman_encoded_data.h"


void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, 
	int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, 
	long int length_of_encoded_image, unsigned char *encoded_image){

	FILE *f = fopen(compressed_file_name_ptr, "w");
	fprintf(f, "# %d\n", image_width);
	fprintf(f, "# %d\n", image_height);
	fprintf(f, "# %d\n", max_gray_value);
	fprintf(f, "# %d\n", number_of_nodes);
	
	// Writing the node pairs
	fprintf(f, "#");
	for(int i = number_of_nodes - 1; i >= 0; i--){
		fprintf(f, " (%d, %d)", huffman_node[i].first_value, huffman_node[i].second_value);
	}
	fprintf(f, "\n");
	
	// Writing the encoding
	fprintf(f, "# %ld\n", length_of_encoded_image);

	fwrite(encoded_image, sizeof(unsigned char), length_of_encoded_image, f);
	
	fclose(f);

	free(huffman_node);
	free(encoded_image);
}