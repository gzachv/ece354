/**
 * CS 354 Assignment 4
 * Author: Gustavo Zach Vargas
 * Section 1
 *
 * This Program creates an array of 100,000 integers. Each element of the 
 * array contains the element such that arr[i] = i where i is the index
 * of each element.
 */

#define SIZE 100000

/* creates an array of integers that can hold 100,000 elements */
int arr[SIZE];


int main(int argc, char* argv[]) {
	int i = 0; /* counter of for loop */
	for (i = 0; i < SIZE; i++) {
		arr[i] = i;
	}

	return 0;
}
