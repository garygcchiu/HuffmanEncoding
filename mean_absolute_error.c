#include "mean_absolute_error.h"

float mean_absolute_error(char *file_name_1_ptr, char *file_name_2_ptr){
	
	struct PGM_Image* image1= malloc(sizeof(struct PGM_Image)); 
	if(load_PGM_Image(image1, file_name_1_ptr) == -1){
		printf("Please ensure you have entered a valid input file.\n");
		exit(0);
	}

	struct PGM_Image* image2 = malloc(sizeof(struct PGM_Image)); 
	if(load_PGM_Image(image2, file_name_2_ptr) == -1){
		printf("Please ensure you have entered a valid input file.\n");
		exit(0);
	}

	if(image1->width != image2->width || image1->height != image2->height){
		printf("Images must be of the same dimensions.\n");
		exit(0);
	}

	float factor1 = 1;
	float factor2 = 1;
	if(image1->maxGrayValue < image2->maxGrayValue){
		factor1 = image2->maxGrayValue / image1->maxGrayValue;
	} else if (image1->maxGrayValue > image2->maxGrayValue){
		factor2 = image1->maxGrayValue / image2->maxGrayValue;
	}

	float error = 0;
	float temp;
	for(int h = 0; h < image1->height; h++){
		for(int w = 0; w < image1->width; w++){
			temp = (image1->image[h][w] * factor1) - (image2->image[h][w] * factor2);
			if(temp < 0){
				temp *= -1;
			}
			error += temp;
		}
	}

	return error / (image1->width * image1->height);
}
