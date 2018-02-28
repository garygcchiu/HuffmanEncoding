#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libpnm.h"

#include "generate_huffman_nodes.h"
#include "store_huffman_encoded_data.h"
#include "huffman_decode_image.h"
#include "read_huffman_encoded_data.h"

int main(int argc, char *argv[]){

	if(argc != 3){
		printf("Please ensure you have entered two arguments. You entered: %d\n", argc - 1);
		exit(0);
	}

	if(access(argv[1], F_OK) == -1){
		printf("Please ensure you have entered a valid compressed file.\n");
		exit(0);
	}

	struct node* huffman_nodes;

	struct header* file_header = malloc(sizeof(struct header));

	unsigned char* encoded_text;
	encoded_text = read_huffman_encoded_data(argv[1], &(file_header->image_width), &(file_header->image_height), 
		&(file_header->max_gray_value), &(file_header->number_of_nodes), &huffman_nodes, 
		&(file_header->length_of_encoded_image));

	printf("\n\n");
	for(int i = 0; i < file_header->number_of_nodes; i++){
		printf("%d %d %d \n", i, huffman_nodes[i].first_value, huffman_nodes[i].second_value);
	}

	// printf("\n\n");
	// for(int i = 0; i < file_header->number_of_nodes * 2; i += 2){
		// printf("%d %d %d \n", i, huffman_nodes[i].first_value, huffman_nodes[i].second_value);
	// }

	// printf("%c\n", encoded_text[0]);
	// printf("%c\n", encoded_text[1]);
	// printf("%c\n", encoded_text[2]);

	return 0;
}