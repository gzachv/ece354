/*
 * intrev.c
 *
 *  Created on: Sep 19, 2014
 *      Author: gzach
 */


/* Written by Gustavo Zach Vargas
 * 9/15/2014
 * cs 354 p1
 * intrev
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

/* This program opens a filewrites each element of an array of integers
 */
int main(int argc, char *argv[])
{
    char *infile;
    char *outfile;
    int fdr;
    int fdw;
    int readNum;
    int *buffArr;
    int fsize;
    int numInt;
    int i;

    /* if a single command line argument is not specified, print usage
     * information and exit
     */
    if (argc != 3) {
	fprintf(stderr, "usage: intrev <file> <file>\n");
	exit(1);
    }

    /* try to open the file to read from */
    infile = argv[1];
    fdr = open(infile,O_RDONLY);
    /* if there was a file open error, print message and exit */
    if(fdr == -1){
	fprintf(stderr, "usage: intrev could not open read file\n");
	exit(1);
    }

    /* try to open the file to write to */
    outfile = argv[2];
    fdw = open(outfile,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR);
    /* if there was a file open error, print message and exit */
    if(fdw == -1){
	fprintf(stderr, "usage: intrev could not open write file\n");
	exit(1);
    }

    /* Determine size of buffer based on file size */
    struct stat fileStat;
    if(fstat(fdr,&fileStat) < 0){
	fprintf(stderr, "usage: intrev could not read from file\n");
	exit(1);
    }
    fsize = fileStat.st_size;/*set fsize based on infor from fstat*/
    numInt = fsize/4;
    /* Dynamically allocate memory for array based on file size*/
    buffArr = malloc(numInt * sizeof(int));

    /* check for end of file or read error (EOF)
     * if either occurs, stop printing data */
    readNum = read(fdr, buffArr , fsize);

    if(readNum == -1){
	fprintf(stderr, "usage: intrev read failure\n");
	exit(1);
    }

    /* traverse array backwards and print contents to file*/
    for(i = numInt-1; i >= 0;  i--){
	if(write(fdw,(buffArr + i),sizeof(int)) == -1){
		fprintf(stderr, "usage: intrev write to file failure\n");
		exit(1);
	}
    }

    /* check if close was successful, if not print error message and exit */
    if(close(fdr) == -1){
	fprintf(stderr, "usage: intrev error closing read  file\n");
	exit(1);
    }

    /* check if close was successful, if not print error message and exit */
    if(close(fdw) == -1){
	fprintf(stderr, "usage: intrev error closing write file\n");
	exit(1);
    }

    return 0;
}

