




	void consumerC() 				//consumer C behaviour
	{

          


	  while(true)
	  {
	    usleep(1000000);
            if(*sim_finish) {printf( "[ ] Consumer C finishes and goes home...\n"); return;} // signal to stop simulation


	    lets_wait(CONSUMER_C_MIN_SLEEP, CONSUMER_C_MAX_SLEEP);
	    printf( "[ ] Consumer C tries to put off the element:...\n");
	 
	    p(mutex_no_AC);                 		// C used, (C,A) avoiding has started
	    
	       
	    p(mutex_read_edit);                 	// read edit forbidden
	   
	    p(empty);

	    if(*read_by_B)
	    {
	     
	      p(mutex_main);                  		// SECTION FORBIDDEN
	      int i = temp[0];
	      pop();                                    // element completely used, removed from queue
	      printf( "[-] Consumer C puts off the element:  %d  \t\t\t\tNumber of elements: %d \t", i , size() )  ;
	      writeDown();
	      (*read_by_B) = 0;                            // reader section reset                          
	      
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
	      printf( "[ ] Consumer C reads the element:  %d  \t\t\t\t\tNumber of elements: %d \t", i , size() )  ;
	      writeDown();
	      (*read_by_C) = 1;
	     
	      v(mutex_read_edit);                      	// read edit allowed 
	      
	      v(mutex_main);                  		// SECTION ALLOWED  
		                     
	      p(mutex_C);                               // C forbidden, anti-repetition
	    }
	  }
	}



