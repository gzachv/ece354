/* Gustavo Zach Vargas
 * CS354 Section 1
 * HW5
 * 
 * Testbench for Mem_Alloc and Mem_Free
 * tests:
 *    a single allocation followed by a free
 *    passes a bad (NULL) pointer to the allocator
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define MEM_SIZE 4096
#define ALLOC_SIZE 35

int main()
{
  /* Create memory space */
  assert(Mem_Init(MEM_SIZE) == 0);
  printf("Memory Space requested with size: %d\n",MEM_SIZE);   
  Mem_Dump();  

  /* Ask for simple memory allocation */
  void* ptr = Mem_Alloc(ALLOC_SIZE);
  printf("\nRequest memory block of size: %d\n",ALLOC_SIZE);
  Mem_Dump();
 
  /* Free memory */
  assert(Mem_Free(ptr) == 0);
  printf("\nFree memory space");
  Mem_Dump();
  
  /* Request memory again*/
  ptr = Mem_Alloc(ALLOC_SIZE);
  printf("\nRequest memory block of size: %d\n",ALLOC_SIZE);
  Mem_Dump();
    
  /* Corrupt pointer */
  ptr = NULL;

  /* Attemp to free memory with bad pointer */
  int result = Mem_Free(ptr);
  printf("Attempted to free memory pointed to by pointer (ptr = %p)\n",ptr);
  printf("Result from Mem_Free(ptr) = %d\n",result);
  Mem_Dump();

  exit(0);
}
