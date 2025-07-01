/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	Image *input=(Image*)malloc(sizeof(Image));
	FILE *fp=fopen(filename,"r");

	int row,col;
	char type[20];
	fscanf(fp, "%s", type);
	fscanf(fp, "%u %u", &input->cols, &input->rows);

	int size;
	fscanf(fp, "%d", &size);

	input->image = (Color **)malloc(sizeof(Color *) * input->rows);
	for(int i=0;i<input->rows;i++){
		input->image[i] = (Color *)malloc(sizeof(Color) * input->cols);
	}
	for (int i = 0; i < input->rows; i++){
		for (int j = 0; j < input->cols;j++){
			fscanf(fp, "%hhu %hhu %hhu", &input->image[i][j].R, &input->image[i][j].G, &input->image[i][j].B);
		}
	}

	fclose(fp);
	return input;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%u %u\n",image->cols,image->rows);
	printf("255\n");
	for (int i = 0; i < image->rows;i++){
		for (int j = 0; j < image->cols;j++){
			printf("%3d %3d %3d", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
			if(j<image->cols-1){
				printf("   ");
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for (int i = 0; i < image->rows;i++){
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}