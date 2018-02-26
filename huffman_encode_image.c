#include "huffman_encode_image.h"

unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, 
	int number_of_nodes, unsigned long int *length_of_encoded_array){

	// Go through and set all of the codes to be 0 by default
	char** codes = malloc(MAX_GRAY_VALUE + 1 * sizeof(char));	
	for(int i = 0; i < MAX_GRAY_VALUE + 1; i ++){
		*(codes[i]) = '0';
	}

	// Generate the codes for each intensity
	struct node cur;
	for(int i = number_of_nodes - 1; i >= 0; i--){
		cur = huffman_node[i];

		// We are always setting the larger number to be 1 concatenated on to the first
		// while the first is simply shifted to the left by 1
		*(codes[cur.second_value]) = (*codes[cur.first_value]) + '1';
		*(codes[cur.first_value]) = (*codes[cur.first_value]) + '0';
	}

	// Go through and add EOF to the end of all of the strings so we know when to stop.
	for(int i = 0; i < MAX_GRAY_VALUE + 1; i ++){
		*(codes[i]) = *(codes[i]) + EOF;
	}

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
			p = 0;

			// add encoding until we reach the EOF we added as the end
			while((cur_char = code[p++]) != EOF){

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
		}
		encoded_image[pos++] = num;
	}

	free(codes);
	return encoded_image;
}
