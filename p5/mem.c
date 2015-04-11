/******************************************************************************
 * FILENAME: mem.c
 * AUTHOR:   cherin@cs.wisc.edu <Cherin Joseph>
 * DATE:     20 Nov 2013
 * PROVIDES: Contains a set of library functions for memory allocation
 * MODIFIED BY: Gustavo Zach Vargas, Section 1
 * *****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "mem.h"


/* this structure serves as the header for each block */
typedef struct block_hd{
  /* The blocks are maintained as a linked list */
  /* The blocks are ordered in the increasing order of addresses */
  struct block_hd* next;

  /* size of the block is always a multiple of 4 */
  /* ie, last two bits are always zero - can be used to store other information*/
  /* LSB = 0 => free block */
  /* LSB = 1 => allocated/busy block */

  /* So for a free block, the value stored in size_status will be the same as the block size*/
  /* And for an allocated block, the value stored in size_status will be one more than the block size*/

  /* The value stored here does not include the space required to store the header */

  /* Example: */
  /* For a block with a payload of 24 bytes (ie, 24 bytes data + an additional 8 bytes for header) */
  /* If the block is allocated, size_status should be set to 25, not 24!, not 23! not 32! not 33!, not 31! */
  /* If the block is free, size_status should be set to 24, not 25!, not 23! not 32! not 33!, not 31! */
  int size_status;

}block_header;

/* Global variable - This will always point to the first block */
/* ie, the block with the lowest address */
block_header* list_head = NULL;


/* Function used to Initialize the memory allocator */
/* Not intended to be called more than once by a program */
/* Argument - sizeOfRegion: Specifies the size of the chunk which needs to be allocated */
/* Returns 0 on success and -1 on failure */
int Mem_Init(int sizeOfRegion)
{
  int pagesize;
  int padsize;
  int fd;
  int alloc_size;
  void* space_ptr;
  static int allocated_once = 0;
  
  if(0 != allocated_once)
  {
    fprintf(stderr,"Error:mem.c: Mem_Init has allocated space during a previous call\n");
    return -1;
  }
  if(sizeOfRegion <= 0)
  {
    fprintf(stderr,"Error:mem.c: Requested block size is not positive\n");
    return -1;
  }

  /* Get the pagesize */
  pagesize = getpagesize();

  /* Calculate padsize as the padding required to round up sizeOfRegio to a multiple of pagesize */
  padsize = sizeOfRegion % pagesize;
  padsize = (pagesize - padsize) % pagesize;

  alloc_size = sizeOfRegion + padsize;

  /* Using mmap to allocate memory */
  fd = open("/dev/zero", O_RDWR);
  if(-1 == fd)
  {
    fprintf(stderr,"Error:mem.c: Cannot open /dev/zero\n");
    return -1;
  }
  space_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (MAP_FAILED == space_ptr)
  {
    fprintf(stderr,"Error:mem.c: mmap cannot allocate space\n");
    allocated_once = 0;
    return -1;
  }
  
  allocated_once = 1;
  
  /* To begin with, there is only one big, free block */
  list_head = (block_header*)space_ptr;
  list_head->next = NULL;
  /* Remember that the 'size' stored in block size excludes the space for the header */
  list_head->size_status = alloc_size - (int)sizeof(block_header);
  
  return 0;
}


/* Function for allocating 'size' bytes. */
/* Returns address of allocated block on success */
/* Returns NULL on failure */
/* Here is what this function should accomplish */
/* - Check for sanity of size - Return NULL when appropriate */
/* - Round up size to a multiple of 4 */
/* - Traverse the list of blocks and allocate the best free block which can accommodate the requested size */
/* -- Also, when allocating a block - split it into two blocks when possible */
/* Tips: Be careful with pointer arithmetic */
void* Mem_Alloc(int size)
{ 
  char* blockPtr;
  int hsize = sizeof(block_header);	/* size of a block header */
  block_header* current = list_head;	/* holds a pointer to the current block in memory being axamined */
  block_header* bestFit = NULL;		/* holds a pointer to the block that best fits the requested size */
  int asize; 				/* holds the acutal size of the block (requested size as multiple of 4 + the size of header */
  int bsize; 				/* holds the usable size of the block (not including header) must be multiple of four (add one if allocated */
  
  /* check for sanity of requested size */
  if (size == 0)
  { 
    return NULL;
  }

  /* Round size to a multiple of 4 and leave room for the header (next and size fields) */
  bsize =  ((size + (4 - 1)) / 4) * 4;
  asize = bsize + hsize;

  /* Traverse list to find best block for given size */ 
  while (current != NULL)
  {
    /* assure block is not allocated (even size), and if it is of appropriate size */
    if (current-> size_status % 2 == 0)
    { 
      if(current->size_status >= asize && (bestFit == NULL || current->size_status < bestFit->size_status)) 
      {
        bestFit = current;
      }  
    }
    current = current->next;
  }

  /* If the best fitting block is still NULL, there is not a block large enough */
  if (bestFit == NULL) 
  {
    return NULL;
  }

  /* set block pointer to allocate to the best block found in the free list */
  blockPtr = (char*)(bestFit + 1);
  
  /* Split block if possible */
  if (bestFit->size_status - asize > 12)
  {
    /*split*/
    block_header* newHeader = (void *)bestFit + asize;
    newHeader->next = bestFit->next;
    bestFit->next = newHeader;
    newHeader->size_status = bestFit->size_status - asize; /* new size is size of block plus the new header size */
    bestFit->size_status = bsize + 1;  
  }  
  else {
    *(int*)(blockPtr - hsize/2) = bsize + 1; /* change size of header to show allocation */  
  }
  
  return (void*)blockPtr; 
}

/* Helper function to coalesce memory
 * params: 
 *        curr - a pointer to the current block
 *        prev - a pointer to the block previous to current
 *        next - a pointer to the block after the current
 **/
void * Coalesce(block_header* currPtr, block_header* prevPtr, block_header* nextPtr)
{
  int size = sizeof(block_header);
 
  /* The allocation status of each block pointer, assume allocated */
  int prev_status = 1; 
  int next_status = 1;
  
  /* Both next and prev are valid */
  if ((prevPtr != NULL) && (nextPtr != NULL))
  { 
    prev_status = prevPtr->size_status & 1;
    next_status = nextPtr->size_status & 1;
  }
  else if (prevPtr == NULL)
  {
    /* There is no prev - curr is at the front of the list */
    prev_status = 1;

    if (nextPtr != NULL)
    {
      next_status = nextPtr->size_status & 1;
    }
  }
  else if (nextPtr == NULL)
  {
    /* There is no next - current is at the end of the list */
    next_status = 1;
    
    if (prevPtr != NULL)
    {
      prev_status = prevPtr->size_status & 1;
    }
  }
  
  /* The previous and next blocks are both allocated */
  if (prev_status && next_status)
  {
    return currPtr;
  }

  /* The previous block is allocated but the next is not */
  else if (prev_status && !next_status)
  {
    size = size + nextPtr->size_status + currPtr->size_status;
    currPtr->size_status = size;
    currPtr->next = nextPtr->next;  
  }

  /* The Previous is free and the next is allocated */
  else if (!prev_status && next_status)
  {
    size = size + prevPtr->size_status + currPtr->size_status;
    prevPtr->size_status = size;
    prevPtr->next = currPtr->next;
    currPtr = prevPtr;
  }

  /* Both previous and next blocks are free */
  else if (!prev_status && !next_status)
  {
    size = (2*size) + prevPtr->size_status + nextPtr->size_status + currPtr->size_status;
    prevPtr->size_status = size;
    prevPtr->next = nextPtr->next;
    currPtr = prevPtr;
  }
 
  return (void*) currPtr;
}

/* Function for freeing up a previously allocated block */
/* Argument - ptr: Address of the block to be freed up */
/* Returns 0 on success */
/* Returns -1 on failure */
/* Here is what this function should accomplish */
/* - Return -1 if ptr is NULL */
/* - Return -1 if ptr is not pointing to the first byte of a busy block */
/* - Mark the block as free */
/* - Coalesce if one or both of the immediate neighbours are free */
int Mem_Free(void *ptr)
{
  block_header* currPtr = NULL;
  block_header* prevPtr = NULL;
  block_header* nextPtr = NULL;
  
  /* check if ptr is valid to be freed */ 
  if (ptr == NULL)
  {
    return -1;
  }
  
  /* Start at list head and iterate through to find ptr */  
  currPtr = list_head;
  nextPtr = currPtr->next;
  while (currPtr != NULL)
  {  
    /* if ptr is found, check status to assure freeable, free the block and coalesce mem space */
    if ((currPtr + 1) == ptr)
    { 
      if ((currPtr->size_status % 2) != 1)
      { 
        return -1; /* the block to be freed is already free */ 
      }
      /* Free a block */
      currPtr->size_status -= 1;
      Coalesce(currPtr, prevPtr, nextPtr);
    }
    
    /* Increment pointers */
    prevPtr = currPtr;
    currPtr = currPtr->next;
    if (currPtr != NULL)
    {
      nextPtr = currPtr->next;
    }
  }
  
  return 0;
}

/* Function to be used for debug */
/* Prints out a list of all the blocks along with the following information for each block */
/* No.      : Serial number of the block */
/* Status   : free/busy */
/* Begin    : Address of the first useful byte in the block */
/* End      : Address of the last byte in the block */
/* Size     : Size of the block (excluding the header) */
/* t_Size   : Size of the block (including the header) */
/* t_Begin  : Address of the first byte in the block (this is where the header starts) */
void Mem_Dump()
{
  int counter;
  block_header* current = NULL;
  char* t_Begin = NULL;
  char* Begin = NULL;
  int Size;
  int t_Size;
  char* End = NULL;
  int free_size;
  int busy_size;
  int total_size;
  char status[5];

  free_size = 0;
  busy_size = 0;
  total_size = 0;
  current = list_head;
  counter = 1;
  fprintf(stdout,"************************************Block list***********************************\n");
  fprintf(stdout,"No.\tStatus\tBegin\t\tEnd\t\tSize\tt_Size\tt_Begin\n");
  fprintf(stdout,"---------------------------------------------------------------------------------\n");
  while(NULL != current)
  {
    t_Begin = (char*)current;
    Begin = t_Begin + (int)sizeof(block_header);
    Size = current->size_status;
    strcpy(status,"Free");
    if(Size & 1) /*LSB = 1 => busy block*/
    {
      strcpy(status,"Busy");
      Size = Size - 1; /*Minus one for ignoring status in busy block*/
      t_Size = Size + (int)sizeof(block_header);
      busy_size = busy_size + t_Size;
    }
    else
    {
      t_Size = Size + (int)sizeof(block_header);
      free_size = free_size + t_Size;
    }
    End = Begin + Size;
    fprintf(stdout,"%d\t%s\t0x%08lx\t0x%08lx\t%d\t%d\t0x%08lx\n",counter,status,(unsigned long int)Begin,(unsigned long int)End,Size,t_Size,(unsigned long int)t_Begin);
    total_size = total_size + t_Size;
    current = current->next;
    counter = counter + 1;
  }
  fprintf(stdout,"---------------------------------------------------------------------------------\n");
  fprintf(stdout,"*********************************************************************************\n");

  fprintf(stdout,"Total busy size = %d\n",busy_size);
  fprintf(stdout,"Total free size = %d\n",free_size);
  fprintf(stdout,"Total size = %d\n",busy_size+free_size);
  fprintf(stdout,"*********************************************************************************\n");
  fflush(stdout);
  return;
}
