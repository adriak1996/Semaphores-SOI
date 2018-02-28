



//****************************************************************************************************************************
//******************************* QUEUE IMPLEMENTATION  **********************************************************************
//****************************************************************************************************************************	


	int peek() {
   		return intArray[(*front)];
	}

	bool isEmpty() {
  		return (*itemCount) == 0;
	}

	bool isFull() {
   		return (*itemCount) == MAX;
	}

	int size() {    // get number elements in queue
   	return (*itemCount);
	}  

	void push(int data) 
	{    // add element at the end of the queue

   		if(!isFull()) 
		{
	
      			if((*rear) == MAX-1) 
			{
         			(*rear) = -1;            
      			}       

     		 	intArray[++(*rear)] = data;
     		 	(*itemCount)++;

  		 	int current = (*front);
   

   			for(int i=0; i<(*itemCount); i++)
   			{

  				 if(current==MAX) current=0;

  				 temp[i]=intArray[current];
  				 ++current;

  			 }


  		 }
	}




	int pop() 
	{                // remove first element form the queue
	   int data = intArray[(*front)++];
	
	   if((*front) == MAX) {
	      (*front) = 0;
	   }
	
	   (*itemCount)--;

	   int current = (*front);
	   

	   for(int i=0; i<(*itemCount); i++)
	   {

	   if(current==MAX) current=0;

	   temp[i]=intArray[current];
	   ++current;

	   }




	   return data;  
	}


	


	void writeDown()             // function to writeDown down the content of the queue
	{
	  if(!writeDown_QUEUE) return;
	  if(size()==0) { printf( "  { Empty list } \n"); return; }
	  printf( "  { "); 
	  
	  for(int i = 0; i <= (size()-1); i++)
	  {
	    printf( "%d ", temp[i]);
	  }
	 printf( " } \n");
	}


//****************************************************************************************************************************
//****************************************************************************************************************************
//****************************************************************************************************************************	





