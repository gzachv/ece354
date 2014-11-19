/**
 * CS 354 Assignment 4
 * Author: Gustavo Zach Vargas
 * Section 1
 *
 * This Program creates an array of 100,000 integers. Each element of the 
 * array contains the element such that arr[i] = i where i is the index
 * of each element.
 */

#include <stdio.h>

#define SIZE 100000

/* creates an array of integers that can hold 100,000 elements */
int arr[SIZE];


int main(int argc, char* argv[]) {
	int i = 0; /* counter of for loop */
	for (i = 0; i < SIZE; i++) {
		arr[i] = i;
	}
	int total_1 = 0;
	int total_2 = 0;
	for (i = 0; i < SIZE/2; i++) {
		total_1+= arr[i];
	}
	for (i = SIZE/2; i < SIZE; i++) {
		total_2+= arr[i];
	}
	fprintf(stdout,"Sum for first half = %d, sum for second half = %d\n",total_1,total_2);
	return 0;
}
