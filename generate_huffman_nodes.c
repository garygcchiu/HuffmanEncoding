#include "generate_huffman_nodes.h"

int max(int x, int y){
	if(x > y){
		return x;
	}
	return y;
}

int min(int x, int y){
	if(x < y){
		return x;
	}
	return y;
}

struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, 
	int number_of_non_zero_values_in_the_frequency_array){

	struct node* nodes = malloc(sizeof(struct node) * number_of_non_zero_values_in_the_frequency_array - 1);

	long cur_min1;
	long cur_min2;

	int cur_pos1;
	int cur_pos2;

	struct node* n;

	for(int i = 0; i < number_of_non_zero_values_in_the_frequency_array - 1; i++){
		
		// Set the current minimum values to be infinity
		cur_min1 = LONG_MAX;
		cur_min2 = LONG_MAX;

		// Go through all fo the elements searching for the lowest two
		for(int p = 0; p < MAX_GRAY_VALUE + 1; p++){
			if(pixel_frequency[p] != 0){
				if(pixel_frequency[p] < cur_min1){

					// Set second lowest to previous lowest
					cur_min2 = cur_min1;
					cur_pos2 = cur_pos1;

					// Set new lowest
					cur_min1 = pixel_frequency[p];
					cur_pos1 = p;

				} else if (pixel_frequency[p] < cur_min2){

					// Set new second lowest
					cur_min2 = pixel_frequency[p];
					cur_pos2 = p;

				}
			}
		}

		// Combine values into a merged node and remove the other node
		pixel_frequency[cur_pos1] += pixel_frequency[cur_pos2];
		pixel_frequency[cur_pos2] = LONG_MAX;

		// Create a new node binding the nodes and save value to return
		n = malloc(sizeof(struct node));
		n->first_value = min(cur_pos1, cur_pos2);
		n->second_value = max(cur_pos1, cur_pos2);
		nodes[i] = *n;

	}

	free(pixel_frequency);
	return nodes;
}
