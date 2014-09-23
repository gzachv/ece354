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

/* strrev opens a file of ASCII numbers and uses a stack to reverse
 * the order and save the results to an output file
 */

/* type def of node in stack */
typedef struct node{
	int value; /* data value stored by node */
	struct node *next; /* pointer to next node in stack */
}Node;


/* 
 * push will add a new node at the head of the list 
 * 
 * @param: oldTOS pointer to old head(top of stack)
 * @return: newTOS pointer to the new head, or 0 for error
 */
Node* push(Node* oldTOS, int valToPush){
	/* dynamically allocate memory for new TOS node */
	Node* newTOS =(Node*) malloc(sizeof(Node));

	if (newTOS == NULL) {
		return 0;
	}
	
	/* populate new node with value to push and next of TOS */
	newTOS->value = valToPush;
	
	/* Hook new node to list */	
	if (oldTOS == NULL) {
		newTOS->next = NULL;		
	}
	else{
		newTOS->next = oldTOS;
	}

	return newTOS;
}

/*
 * pop will remove the node at the top of the stack and return the new head 
 * 
 * @param: oldTOS pointer to old head(top of stack)
 * @return: data value of removed node, or 0 for error
 */
int pop(Node **pstackptr){
	if (pstackptr == NULL || (*pstackptr) == NULL) {
		return 0;
	}

	/* pop from list and reconnect pointers */
	Node *tempNode = *pstackptr;
	int poppedValue = tempNode->value;	
	*pstackptr = tempNode->next;
	free(tempNode);

	return poppedValue;
}

/* Reads a file of ACSII integers and creates output file of
 * the same integers in revers order */
int main(int argc, char *argv[])
{
    char *infile;
    char *outfile;
    FILE *fdr;
    FILE *fdw;
    Node *head_ptr = NULL;    
    int intRead;

     /* if command line arguments are not specified, print usage
     * information and exit
     */
    if (argc != 3) {
        fprintf(stderr, "usage: intrev <infile.int> <outfile_rev>\n");
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
    /* try to open output file */
    outfile = argv[2];
    fdw = fopen(outfile,"w");
    /* if there was a file open error, print message and exit */
    if (fdw == NULL) {
        fprintf(stderr, "usage: strtoboth error opening outfile 1\n");
        exit(1);
    }

    /* Read in data check for end of file or read error (EOF) and push data onto stack
     * if either occurs, stop printing data */
     while (fscanf(fdr, "%d\n", &intRead) != EOF) {
	head_ptr = push(head_ptr,intRead);
     }
 
    /* pop data from stack and write to output file so that is is output in reverse order */
    while (head_ptr != NULL) {
	fprintf(fdw, "%d\n",pop(&head_ptr));
    }

    /* Read in data check for end of file or read error (EOF) and push data onto stack
     * check if input file close was successful, if not print error message and exit */
    if (fclose(fdr) != 0) {
         fprintf(stderr, "usage: strtoboth error closing input file\n");
         exit(1);
     }

     /* check if first output file close was successful, if not print error message and exit */
     if (fclose(fdw) != 0) {
         fprintf(stderr, "usage: strtoboth error closing output1 file\n");
         exit(1);
     }

     return 0;
}
