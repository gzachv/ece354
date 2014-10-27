/* Assignment 3
 * by Gustavo Zach Vargas, Section 1
 * 
 * TODO 
 * description
 * static needed?
 */

#include <stdio.h>

#define MAXSIZE sizeof(int)

static int divisionCnt = 0; /* counter to store the number of successful division ops */

int main(int argc, char* argv[]) {
  
  char input[MAXSIZE];
  int num; /* numerator for division */
  int denom; /* denominator for division */

  while (1){
    printf("Enter first integer: ");
    fgets(input, MAXSIZE ,stdin);
    num = atoi(input);
    printf("Enter second integer: ");
    fgets(input, MAXSIZE ,stdin);
    denom = atoi(input); 
    printf("%d / %d is \n",num, denom); 
  }

}
