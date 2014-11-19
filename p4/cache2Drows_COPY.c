/**
 * CS 354 Assignment 4
 * Author: Gustavo Zach Vargas
 * Section 1
 *
 * This Program creates a 2D array of integers with dimenstions: 3000 rows X 500 cols. Each element of the 
 * array contains the element such that arr2d[row][col] = row + col where row and col are the indecies
 * of each element.
 */

#include <stdio.h>

#define NUMROW 3000
#define NUMCOL 500

/* creates a 2d array of integers */
int arr2d[NUMROW][NUMCOL];

/**
 * Main method will initialize the 2d array with each element equal to the sum of its indicies
 */
int main(int argc, char* argv[]) {
	int row = 0; /* row counter of for loop */
	int col = 0; /* col counter of for loop */
	for (row = 0; row < NUMROW; row++) {
		fprintf(stdout,";\n");
		for (col = 0; col < NUMCOL; col++) {
			arr2d[row][col] = row + col;
			fprintf(stdout,"%d, ",arr2d[row][col]);
		}
	}
	return 0;
}
