#include "huffman_encode_image.h"

unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, 
	int number_of_nodes, unsigned long int *length_of_encoded_array){

	// Go through and set all of the codes to be 0 by default
	char** codes = malloc((MAX_GRAY_VALUE + 1) * sizeof(char*));	
	for(int i = 0; i < MAX_GRAY_VALUE + 1; i ++){
		codes[i] = malloc(sizeof(char) * 17);
		codes[i][0] = 0;
	}

	// Generate the codes for each intensity
	struct node cur;
	int uninitialized;
	int initialized;
	for(int i = number_of_nodes; i >= 0; i--){
		cur = huffman_node[i];

		// printf("Node: %d %d\n\n", cur.first_value, cur.second_value);

		if(codes[cur.first_value][0] == 0){
			uninitialized = cur.first_value;
			initialized = cur.second_value;
		} else {
			initialized = cur.first_value;
			uninitialized = cur.second_value;
		}

		// Copying the code for the first value to the second
		for(int j = 1; j <= codes[initialized][0]; j++){
			// number of elements in the code
			codes[uninitialized][0] += 1;
			// using position in the code and code from first one (being copied)	
			codes[uninitialized][(int)(codes[uninitialized][0])] = codes[initialized][j];
		}

		codes[uninitialized][0] += 1;
		codes[uninitialized][(int)(codes[uninitialized][0])] = '1';

		codes[initialized][0] += 1;
		codes[initialized][(int)(codes[initialized][0])] = '0';
	}


	//* Debugging: Print the huffman codes *//
	// for(int i = 0; i < MAX_GRAY_VALUE + 1; i ++){
	// 	if(codes[i][0] != 0){
	// 		printf("\n\n---- %d %d ---- \n", i, codes[i][0]);
	// 		for(int j = 1; j <= codes[i][0]; j++){
	// 			printf("%c", codes[i][j]);
	// 		}
	// 		printf("\n");
	// 	}
	// }


	unsigned char* encoded_image = calloc(input_pgm_image->width * input_pgm_image->height, 
		sizeof(unsigned char));

	char* code;					// the code generated above for a particular intensity
	unsigned char num = 0x00;	// the current unsigned char (encoded)
	int pos = 0;				// number of encoded items
	int cur_shift = 0;			// number of bits encoded for current encoding
	char cur_char;				// current character of encoding
	int p;						// position in the encoding

	for(int i = 0; i < input_pgm_image->height; i++){
		for(int j = 0; j < input_pgm_image->width; j++){

			
			// get the generated code for this intensity
			code = codes[input_pgm_image->image[i][j]];

			// printf("\nValue: %d\n", input_pgm_image->image[i][j]);

			for(p = 0; p <= code[0]; p++){
				cur_char = code[p];

				// once we reach 8 bits we have reached the limit of a single unsigned char
				if(cur_shift == 8){

					// add to the encoded image and rest
					encoded_image[pos++] = num;
					num = 0x00;
					cur_shift = 0;
				}

				// always shift by 1, only add one if necessary
				num = num << 1;
				if(cur_char == '1'){
					num += 0x01;
				}
				cur_shift++;
			}
		}
	}

	// Dealing with the final encoding, need to move it to the left by shifting it
	// an appropriate number of times
	if(cur_shift != 0){
		while(cur_shift != 0){
			num = num << 1;
			cur_shift++;

			if(cur_shift == 8){
				cur_shift = 0;
			}
		}
		encoded_image[pos++] = num;
	}

	*length_of_encoded_array = pos - 1;

	for(int i = 0; i < MAX_GRAY_VALUE + 1; i ++){
		free(codes[i]);
	}
	free(codes);
	return encoded_image;
}
