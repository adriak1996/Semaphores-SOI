




void producer()   					// producer behaviour
	{



	  for(int i=0;i<40;++i)   			// producer creates 40 elements, first 17 in fast mode, the other in slow mode
	  {

	    if(i<17)
	    lets_wait(PRODUCER_MIN_SLEEP, PRODUCER_MAX_SLEEP);
	    else
	    lets_wait(_PRODUCER_MIN_SLEEP, _PRODUCER_MAX_SLEEP);

	    printf( "[ ] The producer tries to insert a element into the queue...\n");   
	   
	    p(full);   					// anti-overloading blockade
	   
	    p(mutex_main);  				// access to section blockade lock
	    push(i);     				// adding new element to queue
	    printf( "[+] The producer inserts the element into the queue...   \t\tNumber of elements: %d \t", size() )  ;
	    writeDown(); 

	    
	    v(mutex_main);     				// access to section blockade release
	   
	    v(empty);       				// blockade against empty queue release
	  }

	printf( "[ ] The producer finishes and goes home...\n"); 
        *sim_finish=1;
        v(mutex_main);
        v(empty);

	return;


	      
	}



