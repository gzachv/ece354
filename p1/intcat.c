/* Written by Gustavo Zach Vargas
 * 9/15/2014
 * cs 354 p1
 * intcat
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

#define MAX sizeof(int)

/* This program reads an ACII file containing numbers
 * and writes the contents to the console as human readable ASCII
 */
int main(int argc, char *argv[])
{
	char *infile;
	int fd;
	int readNum;
	int intRead;

	/* if a single command line argument is not specified, print usage
	 * information and exit
	 */
	if (argc != 2) {
		fprintf(stderr, "usage: intcat <file>\n");
		exit(1);
	}

	/* try to open the file */
	infile = argv[1];
	fd = open(infile,O_RDONLY);
	/* if there was a file open error, print message and exit */
	if(fd == -1){
		fprintf(stderr, "usage: intcat file read error\n");
		exit(1);
	}

	/* read data while not at end of file and no error
	 * if either occurs, stop printing data */
	readNum = read(fd, &intRead, MAX);
	
	while (readNum != 0){
		
		if (readNum == -1){
			fprintf(stderr, "usage: incat read failure\n");
			exit(1);
		}
		
		printf("%d\n",intRead);
		readNum = read(fd, &intRead, MAX);
	}

	/* check if close was successful, if not print error message and exit */
	if(close(fd) == -1){
		fprintf(stderr, "usage: intcat error closing file\n");
		exit(1);
	}

	return 0;
}



