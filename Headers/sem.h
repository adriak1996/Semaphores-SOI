

#ifndef __sem_h
#define __sem_h

#include <stdio.h> 
#include <stdlib.h> 

#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h>

#include <stdbool.h>



//****************************************************************************************************************************
//******************************* NECESSARY CONSTANS *************************************************************************
//****************************************************************************************************************************

// Global declaration to using shared semaphores
#define MUTEX1 "/mutex1"
#define FULL "/full"
#define EMPTY "/empty"
#define A "/A"
#define B "/B"
#define C "/C"
#define AC "/AC"
#define READ "/read"
//

	const int QUEQE_SIZE = 9;                // Maximum number of elements in the queue

	const bool writeDown_QUEUE = 1;              // flag, if writeDown whole the queue (1 when true)

// time in seconds
	const int CONSUMER_A_MAX_SLEEP = 4; 
	const int CONSUMER_B_MAX_SLEEP = 5;
	const int CONSUMER_C_MAX_SLEEP = 6;
	const int PRODUCER_MAX_SLEEP   = 2; 

	const int CONSUMER_A_MIN_SLEEP = 3;
	const int CONSUMER_B_MIN_SLEEP = 4;
	const int CONSUMER_C_MIN_SLEEP = 5;
	const int PRODUCER_MIN_SLEEP   = 1; 
//

//slow producer mode
	const int _PRODUCER_MAX_SLEEP   = 10; 
	const int _PRODUCER_MIN_SLEEP   = 5; 
//


//****************************************************************************************************************************
//******************************* QUEUE's VARIABLES **************************************************************************
//****************************************************************************************************************************

//      Queue's variables
	#define MAX 9

	int* intArray;
	int* temp;
	int* front;
	int* rear;
	int* itemCount;


//****************************************************************************************************************************
//******************************* RANDOM TIME PEROID GENERATOR ***************************************************************
//****************************************************************************************************************************

	void lets_wait(int _min, int _max) // function to generate random period of time to creating new proccesses of producer and customers
	{                                      //_min and _max means minimal and maximal values to generate 
 		 usleep(       (     (rand() % (_max - _min))     + _min)     *1000000);


	}


//****************************************************************************************************************************
//******************************* SEMAPHORES *********************************************************************************
//****************************************************************************************************************************

	sem_t* mutex_main;       // blockade against more than one proccesses use 
	sem_t* full;    	 // blockade against full queue 
	sem_t* empty;            // blockade against empty queue 
	sem_t* mutex_A;          // blockade against reading the element more than one by the consumer A
	sem_t* mutex_B;          // blockade against reading the element more than one by the consumer B
	sem_t* mutex_C;          // blockade against reading the element more than one by the consumer C
	sem_t* mutex_no_AC;      // blockade against non-accepted situation (when C tries to read after A did it and vice versa)
	sem_t* mutex_read_edit;  // blockade simultinous against modification of : read_by_A, read_by_B  or read_by_C by more than one proccess



//****************************************************************************************************************************
//******************************* FLAGS CHECKING READING *********************************************************************
//****************************************************************************************************************************

	bool* read_by_A;                  // flag, if element was read by A (1 when true)
	bool* read_by_B;                  // flag, if element was read by B (1 when true)
	bool* read_by_C;                  // flag, if element was read by C (1 when true)
        bool* sim_finish;                 // flag, appoint when simulation should stop (1 when true)


//****************************************************************************************************************************
//******************************* FUNCTIONS OF SEMAPHORE *********************************************************************
//****************************************************************************************************************************
	void constructor(sem_t* s, const int value )  // semaphore constructor
	{
  		sem_init( s, 0, value );
	}

	void destructor(sem_t* s)   // semaphore destructor
	{ 
		sem_destroy(s ); 
	}


	void p(sem_t* s)          // set a blockade on semaphore, -1
	{
  		sem_wait( s );
	}

	void v(sem_t* s)          // release a blockae, +1      
	{
  		sem_post( s );
	}



	sem_t* sem_creator(const char *name, unsigned value)        // create new semaphore instance or connect semaphore with shared memory
	{
	 sem_t* temp = sem_open(name,  O_CREAT | O_EXCL, S_IRWXU | S_IRWXG, value);

	 

		 if( temp == SEM_FAILED )
	    {
		temp = sem_open(name, O_RDWR);
		
		return temp; 
	    }

	return temp;

	}


//****************************************************************************************************************************
//******************************* SHARED MEMORY INITIALIZATION ***************************************************************
//****************************************************************************************************************************
	void do_init()   // initialize shared memory blocks and appoint references to them
	{
		 int shmidA, shmidB, shmidC, shmidArray, shmidTemp, shmidS, shmidF, shmidR, shmidStop; // reference to memory blocks
	   	 key_t keyA, keyB, keyC, keyArray, keyTemp, keyS, keyF, keyR, keyStop; // key which defined allocated blocks

	   	 keyA =5350;
	   	 keyB = 5351;
	   	 keyC = 5352;
	   	 keyArray = 5353;
	    	 keyTemp = 5354;
	    	 keyS = 5355;
	   	 keyF = 5356;
	   	 keyR = 5357;
		 keyStop = 5358;


		// creating shared semaphored or connecting them with existed instances
		mutex_main = sem_creator(MUTEX1, 1);
		full = sem_creator(FULL, MAX);
		empty = sem_creator(EMPTY, 0);
		mutex_A = sem_creator(A, 0);
		mutex_B = sem_creator(B, 0);
		mutex_C = sem_creator(C, 0);
		mutex_no_AC = sem_creator(AC, 1);
		mutex_read_edit = sem_creator(READ, 1);
		//
	  





	    //creating reference with shared memory blocks
	    shmidA = shmget(keyA, sizeof(bool), IPC_CREAT | 0666); 
	    shmidB = shmget(keyB, sizeof(bool), IPC_CREAT | 0666);
	    shmidC = shmget(keyC, sizeof(bool), IPC_CREAT | 0666);
	    shmidStop = shmget(keyStop, sizeof(bool), IPC_CREAT | 0666);
	    shmidArray = shmget(keyArray, MAX*sizeof(int), IPC_CREAT | 0666);
	    shmidTemp = shmget(keyTemp, MAX*sizeof(int), IPC_CREAT | 0666);
	    shmidS = shmget(keyS, sizeof(int), IPC_CREAT | 0666);
	    shmidF = shmget(keyF, sizeof(int), IPC_CREAT | 0666);
	    shmidR = shmget(keyR, sizeof(int), IPC_CREAT | 0666);
	    //


	    //contecting variables with references to memory blocks
	    read_by_A = shmat(shmidA, NULL, 0);
	    read_by_B = shmat(shmidB, NULL, 0);
	    read_by_C = shmat(shmidC, NULL, 0);
            sim_finish = shmat(shmidStop, NULL, 0);
	    intArray = shmat(shmidArray, NULL, 0);
	    temp = shmat(shmidTemp, NULL, 0);
	    itemCount = shmat(shmidS, NULL, 0);
	    front = shmat(shmidF, NULL, 0);
	    rear = shmat(shmidR, NULL, 0);
	    //


	}


//****************************************************************************************************************************
//*************************************************************((((((((((((((((***********************************************
//****************************************************************************************************************************
	



	#endif



