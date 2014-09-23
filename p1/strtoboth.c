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

/* This program reads strings from an ASCII and outputs 
 * one file in integer format and one file in modified ASCII
 * modified ASCII file (.str2) must be read with cat (since it is not classic ASCII)
 */
int main(int argc, char *argv[])
{
    char *infile;
    char *outfile2;
    FILE *fdr;
    FILE *fdw2;
    int writefile;
    int intRead;

    /* if command line arguments are not not specified, print usage
     * information and exit
     */
    if (argc != 4) {
	fprintf(stderr, "usage: strtoboth <infile.str> <outfile1.int> <outfile2.str2>\n");
	exit(1);
    }

    /* try to open the input file */
    infile = argv[1];
    fdr = fopen(infile,"r");
    /* if there was a file open error, print message and exit */
    if (fdr == NULL) {
	fprintf(stderr, "usage: strtoboth error opening read file\n");
	exit(1);
    }

    /* try to open the first output file */
    writefile = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR);
    /* if there was a file open error, print message and exit */
    if (writefile == -1) {
	fprintf(stderr, "usage: strtoboth error opening outfile 1\n");
	exit(1);
    }

    /* try to open the second output file */
    outfile2 = argv[3];
    fdw2 = fopen(outfile2,"w");
    /* if there was a file open error, print message and exit */
    if (fdw2 == NULL){
	fprintf(stderr, "usage: strtoboth error opening outfile 2\n");
	exit(1);
    }

    /*print data to output files as modified ASCII and as int, respectivly:
     * Read in data check for end of file or read error (EOF) and print data
     * if either occurs, stop printing data
     */
    while (fscanf(fdr, "%d\n", &intRead) != EOF) {
	if (intRead < 0) {
		fprintf(fdw2, "- %d;\n", abs(intRead));
	}      
	else{
		fprintf(fdw2, "%d;\n", intRead);
	}

	/* write to binary file as integers */
	if (write(writefile, &intRead, sizeof(int)) != sizeof(int)) {
           	 fprintf (stderr, "usage: strtoboth bad write to file \n");
           	 exit(1);
            }
    }


    /* close read and output files:
     * check if input file close was successful, if not print error message and exit 
     */
    if (fclose(fdr) != 0) {
	fprintf(stderr, "usage: strtoboth error closing input file\n");
	exit(1);
    }

    /* check if second output file close was successful, if not print error message and exit */
    if (fclose(fdw2) != 0) {
	fprintf(stderr, "usage: strtoboth error closing output2 file\n");
	exit(1);
    }

    /* close output file 1 and input file
     * check if first output file close was successful, if not print error message and exit
     */
    if (close(writefile) == -1) {
	fprintf(stderr, "usage: strtoboth error closing output1 file\n");
	exit(1);
    }

    return 0;
}

