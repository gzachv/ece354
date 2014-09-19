/*
 * strtoboth.c
 *
 *  Created on: Sep 19, 2014
 *      Author: gzach
 */


/* Written by Gustavo Zach Vargas
 * 9/15/2014
 * cs 354 p1
 * strtoboth
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

#define MAX sizeof(int)

/* This program reads strings from a file and displays them
 * to the console.
 */
int main(int argc, char *argv[])
{
    char *infile;
    char *outfile1;
    char *outfile2;
    FILE *fdr;
    FILE *fdw1;
    FILE *fdw2;
    char buffer[MAX];

    /* if a single command line argument is not specified, print usage
     * information and exit
     */
    if (argc != 4) {
	fprintf(stderr, "usage: strtoboth <file>\n");
	exit(1);
    }

    /* try to open the input file */
    infile = argv[1];
    fdr = fopen(infile,"r");
    /* if there was a file open error, print message and exit */
    if(fdr == NULL){
	fprintf(stderr, "usage: strtoboth error opening read file\n");
	exit(1);
    }

    /* try to open the first output file */
    outfile1 = argv[2];
    fdw1 = fopen(infile,"r");
    /* if there was a file open error, print message and exit */
    if(fdw1 == NULL){
	fprintf(stderr, "usage: strtoboth error opening outfile 1\n");
	exit(1);
    }

    /* try to open the second output file */
    outfile2 = argv[3];
    fdw2 = fopen(infile,"r");
    /* if there was a file open error, print message and exit */
    if(fdw2 == NULL){
	fprintf(stderr, "usage: strtoboth error opening outfile 2\n");
	exit(1);
    }

    /* check for end of file or read error (EOF)
     * if either occurs, stop printing data */
    while(fscanf(fdr, "%s/n", buffer) != EOF){
	printf("%d\n",(int)buffer);
    }

    /* check if close was successful, if not print error message and exit */
    if(fclose(fdr) != 0){
	fprintf(stderr, "usage: strtoboth error closing file\n");
	exit(1);
    }

    return 0;
}

