/*
 * strrev.c
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

/* strrev opens a file of ASCII numbers and uses a stack to reverse
 * the order and save the results to an output file */

/* type def of node in stack */
typedef struct node{
	int value; /* data value stored by node */
	struct node *next; /* pointer to next node in stack */
}Node;


/* push will add a new node at the head of the list 
 * 
 * @param: oldTOS pointer to old head(top of stack)
 * @return: newTOS pointer to the new head, or 0 for error
 */
Node* push(Node* oldTOS, int valToPush){
	/* dynamically allocate memory for new TOS node */
	Node* newTOS =(Node*) malloc(sizeof(Node));

	if(newTOS == NULL){
		return 0;
	}
	
	/* populate new node with value to push and next of TOS */
	newTOS->value = valToPush;
	
	/* Hook new node to list */	
	if(oldTOS == NULL){
		newTOS->next = NULL;		
	}
	else{
		newTOS->next = oldTOS;
	}

	return newTOS;
}

/* pop will remove the node at the top of the stack and return the new head 
 * 
 * @param: oldTOS pointer to old head(top of stack)
 * @return: newTOS pointer to the new head, or 0 for error
 */

