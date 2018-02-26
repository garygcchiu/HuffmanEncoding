#include "generate_pixel_frequency.h"

long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, 
	int *number_of_non_zero_values_in_the_frequency_array){

	// Dynamically allocates long int array
	long int* pixels = calloc(MAX_GRAY_VALUE + 1, sizeof(long int));
	
	// Going through each pixel in the image
	for(int i = 0; i < input_pgm_image->height; i++){
		for(int j = 0; j < input_pgm_image->width; j++){

			int cur = input_pgm_image->image[i][j];
			
			// Increase the count of pixels with this intensity
			pixels[cur]++;

			// Increment the number of non zero values if applicable
			if(cur != 0){
				(*number_of_non_zero_values_in_the_frequency_array)++;
			}
		}
	}
	return pixels;
}
