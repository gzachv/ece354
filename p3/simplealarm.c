/* Assignment 3 
 * by Gustavo Zach Vargas, Section 1
 *
 * This program contains is a simple alarm program. The alarm is armed
 * and set to go off every one seconds. When the alarm 'sounds' it 
 * triggers a SIGALRM interrupt.
 */


/*
 * TODO 
 * do we have to check the return value of alarm
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

static int armTime = 1;

/*
 *
 */
static void handler(int signum) {
   time_t curtime;
  
   /* 
    * Calling time with a non-NULL param causes the current time to be stored
    * at the memory pointed to by curtime
    */ 
   time(&curtime);

   printf("\ncurrent time is %s", ctime(&curtime));

   alarm(armTime);
}

/* 
 *
 */
int main(int argc, char* argv[]) {

 fprintf(stdout, "Enter ^C to end the program:\n");

 struct sigaction sa;
 int counter = 0; /* a counter for the random number */
 int cntMax = 0; /* variable to store the number to count up to */

 sa.sa_handler = handler;
 sigemptyset(&sa.sa_mask);
 sa.sa_flags = SA_RESTART;

 srandom(1); /* seed a random number generator */

 /* arms the SIGALRM to go off in one second */
 alarm(armTime);

 while(1) {

   cntMax = (random()%10)*10000000;

   for (counter = 0; counter < cntMax; counter++) {
   }

   printf("."); 
 
   if (sigaction(SIGALRM, &sa, NULL) == -1) {
     fprintf(stderr, "Error calling sigaction. Quitting.");
     exit(1);
   }
 }

} 
