
// Producer-Consumer Issue; 1 producer, 3 consumers

// Required conditions to put off the first element of the queue:
// 1. element was read by A and B  
// or      
// 2. element was read by B and C

// The other important conditions of this simulation:
// A, B and C cannot read an element more than once
// and
// if an element was read by A, C cannot read it and vice versa


 
// Author: KOTOWSKI Adrian

 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Headers/sem.h"
#include "../Headers/queue.h"
#include <pthread.h>




int main()  // starter proccess
{
   	

        sem_unlink(MUTEX1);
        sem_unlink(FULL);
  	sem_unlink(EMPTY);
	sem_unlink(A);
	sem_unlink(B);
 	sem_unlink(C);
	sem_unlink(AC);
	sem_unlink(READ);


printf( "\nSimulation starts...\n");  
  do_init();
  *read_by_A=0;
  *read_by_B=0;
  *read_by_C=0;
  *sim_finish=0;
  *itemCount = 0;
  *front = 0;
  *rear = -1;


 

  



  return 0;
}
