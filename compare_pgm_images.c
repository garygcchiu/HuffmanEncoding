#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libpnm.h"

#include "mean_absolute_error.h"

int main(int argc, char *argv[]){

	// Checking args
	if(argc != 3){
		printf("Please ensure you have entered two arguments. You entered: %d\n", argc - 1);
		exit(0);
	}

	// Checking that args represent valid files
	if(access(argv[1], F_OK) == -1 || access(argv[1], F_OK) == -1){
		printf("Please ensure you have entered two valid files.\n");
		exit(0);
	}

	// Checking the mean absolute error
	float error = mean_absolute_error(argv[1], argv[2]);

	printf("The mean absolute error between the two images is: %f\n", error);
	
	return 0;
}