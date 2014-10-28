/* Assignment 3 
 * by Gustavo Zach Vargas, Section 1
 *
 * This program contains is a simple alarm program. The alarm is armed
 * and set to go off every one seconds(specified by global variable armTime).
 * When the alarm 'sounds' it triggers a SIGALRM interrupt and prints the current time.
 * The program also
 * counts up to a random number between 0 and ninety million (increments of ten million).
 * The purpose of the coutning in the infinite loop is simply to waste processor time.
 * Each time the count is completed, a single period char is printed.
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

/* handler is the interrupt handler for the SIGINT signal triggered when the alarm
 * library function is triggered. The handler prints the current time and rearms the alarm.
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

/* The main method sets up an interrupt handler and then enters an infinite loop.
 * In this loop the program counts up to a random (seeded) number between 0 and ninty million
 * (increments of 10 million).
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

   cntMax = (random()%10)*10000000; /* takes the last digit of a random, scales it by 10 million*/

   for (counter = 0; counter < cntMax; counter++) {
   }

   printf("."); 
 
   if (sigaction(SIGALRM, &sa, NULL) == -1) {
     fprintf(stderr, "Error calling sigaction. Quitting.");
     exit(1);
   }
 }

} 
