






	void consumerA()   				//consumer A behaviour
	{
	  while(true)
	  {
            usleep(1000000);
	    if(*sim_finish) { printf( "[ ] Consumer A finishes and goes home...\n"); return;} // signal to stop simulation


	    lets_wait(CONSUMER_A_MIN_SLEEP, CONSUMER_A_MAX_SLEEP);
	    printf( "[ ] Consumer A tries to put off the element:...\n"); 
		  
	    p(mutex_no_AC);                		 // A used, (C,A) avoiding has started   
	    
	    p(mutex_read_edit);            		 // read edit forbidden        
	   
	    p(empty); 


	    if(*read_by_B)
	    {
	    
	      p(mutex_main);                  		 // SECTION FORBIDDEN
	      int i = temp[0];
	      pop();                                 	 // element completely used, removed from queue
	      printf( "[-] Consumer A puts off the element:  %d    \t\t\t\tNumber of elements: %d \t", i , size() ) ;
	      writeDown();
	      (*read_by_B) = 0;    
	     
	      v(full);                                 	// reader section reset   
	    
	      v(mutex_read_edit);                      	// read edit allowed
	     
	      v(mutex_main);                  		// SECTION ALLOWED
	     
	      v(mutex_no_AC);                          	// (A,C) avoiding has finished
	      
	      v(mutex_A);                              	// A allowed, section reset
	     
	      v(mutex_B);                              	// B allowed, section reset
	     
	      v(mutex_C);                              	// C allowed, section reset
	    }
	    else
	    {
	     
	      v(empty);
	     
	      p(mutex_main);                  		// SECTION FORBIDDEN
	      int i = temp[0];
	      printf( "[ ] Consumer A reads the element:  %d  \t\t\t\t\tNumber of elements: %d \t", i , size() )  ;
	      writeDown();
	      (*read_by_A) = 1;
	     
	      v(mutex_read_edit);                       // read edit allowed
	     
	      v(mutex_main);                 	 	// SECTION ALLOWED
	     
	      p(mutex_A);                              	// A forbidden, anti-repetition
	    }
	  }
	}





