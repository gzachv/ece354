/*
 * strcat.c
 *
 *  Created on: Sep 19, 2014
 *      Author: gzach
 */


/* Written by Gustavo Zach Vargas
 * 9/15/2014
 * cs 354 p1
 * strcat
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
    FILE *fd;
    char buffer[MAX];

    /* if a single command line argument is not specified, print usage
     * information and exit
     */
    if (argc != 2) {
	fprintf(stderr, "usage: strcat <file>\n");
	exit(1);
    }

    /* try to open the file */
    infile = argv[1];
    fd = fopen(infile,"r");
    /* if there was a file open error, print message and exit */
    if(fd == NULL){
	fprintf(stderr, "usage: strcat <file>\n");
	exit(1);
    }

    /* check for end of file or read error (EOF)
     * if either occurs, stop printing data */
    while(fscanf(fd, "%s/n", buffer) != EOF){
	printf("%s\n",buffer);
    }

    /* check if close was successful, if not print error message and exit */
    if(fclose(fd) != 0){
	fprintf(stderr, "usage: strcat error closing file\n");
	exit(1);
    }

    return 0;
}

