/* Assignment 3
 * by Gustavo Zach Vargas, Section 1
 *
 * This program conducts a simple dividion operation given user input for two integers.
 * The program asks the user for input of each int and prints out the quotient and remainder values.
 * Additionally, the program monitors for interrrupts of SIGINT (caused by ^C) and SIGFPE from
 * divide by zero errors. These interrupts are handled by specified handlers.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAXSIZE 500  /*maximum size of buffer */

static int divisionCnt = 0; /* counter to store the number of successful division ops */

/* zDenomHandler is the interrupt handler that is taken when a SIGFPE signal occurs
 *   due to a divide by zero operation. The handler prints an appropriate message and 
 *   exits the program 'gracfully'
 *
 */
static void zDenomHandler(int signum) {
 fprintf(stderr, "Usage: Zero as denominator, a divide by zero error occured. Quitting.\n");
 exit(1);
}

/* fstopHandler is the interrupt handler that is taken when a SIGINT signal occurs
 *   due to a force stop envokation via ^C command. The handler prints an appropriate message and 
 *   exits the program 'gracfully'
 *
 */
static void fstopHandler(int signum) {
 fprintf(stderr, "\nUsage: Force stop triggered a total of %d division occured. Quitting.\n",divisionCnt);
 exit(1);
}

/* The main method of this program sets up necessary variables including associating handlers with 
 *   specific interrups and then enters an infinite loop where it requests input for the 
 *   integers used in the division opteration.
 *
 */
int main(int argc, char* argv[]) {
  
  char input[MAXSIZE];
  int num; /* numerator for division */
  int denom; /* denominator for division */
  struct sigaction zDenom; /* sigaction struct for zero in denom */
  struct sigaction fstop; /* sigaction struct for force stop ^C */ 

  /* set up the handlers for the interrupt signals,
   * first select the handler method to go to upon a signal
   * next, initializes empty signal set
   * finally it sets the restart flag so that if a function is interrupted 
   * the handler it will restart after the handler is done
   */
  zDenom.sa_handler = zDenomHandler;
  if (sigemptyset(&zDenom.sa_mask) == -1) {
      fprintf(stderr, "Error in signal set initialization. Quitting.");
      exit(1);
  }
  zDenom.sa_flags = SA_RESTART;

  fstop.sa_handler = fstopHandler;
  if (sigemptyset(&fstop.sa_mask) == -1) {
      fprintf(stderr, "Error in signal set initialization. Quitting.");
      exit(1);
  }
  fstop.sa_flags = SA_RESTART;
  
  while (1){
    /* sets up listening for SIGINT signal*/
    if (sigaction(SIGINT, &fstop, NULL) == -1){
      fprintf(stderr, "Error in sigaction. Quitting.");
      exit(1);
    }

    /* Ask for and get first integer: the numerator */
    printf("Enter first integer: ");
    if (fgets(input, MAXSIZE, stdin) == NULL) {
        fprintf(stderr, "Error in fgets. Quitting.");
        exit(1);
    }

    num = atoi(input); /* convert to integer*/

    /* Ask for and get second integer: the denominator */
    printf("Enter second integer: ");
    if (fgets(input, MAXSIZE ,stdin) == NULL){
        fprintf(stderr, "Error in fgets. Quitting.");
        exit(1);
    }

    denom = atoi(input); /*convert to integer*/
     
    /* sets up listening for SIGINT signal*/
    if (sigaction(SIGFPE, &zDenom, NULL) == -1) {
        fprintf(stderr, "Error in sigaction. Quitting.");
        exit(1);
    }
    
    printf("%d / %d is %d with a remainder of %d\n",num, denom,num/denom,num%denom);
    
    divisionCnt++; /*increment the number of divisions completed*/
  }

}
