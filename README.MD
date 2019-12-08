
## DESCRIPTION 
- This is an academic project in C under Linux OS, prepared for the course 'Operating Systems'.

- The project shows application of semaphores to solve problem of producer and customers.

- A producer inserts resources to a queue and simultinous, consumers want to take 
   resources from queue, each one separately.

- There are one producer and three consumers.

- All the particiants may use resources in the same time, so it is necessary to provide 
   control of access to a critical section.

- Each consumer wants to read first element in the queue and if element was read twice,
   it is removed from the queue by the second reader (customer).

- There are also condition, if an element was read by the consumer A, the consumer C cannot read it and vice versa, 
   if an element was read by the consumer C, the consumer A cannot read it too.

- In addition, the producer cannot add an element to the full queue 
   and the customers cannot remove an element form the empty queue. 

- Written in C with proccesses ( ASSUMPTION: NOT TO USE C++ AND THREADS )


## GUIDE 
1. HOW TO START SIMULATION
   Run script *start.sh* from *LinuxRun* dir in shell to start simulation

1. HOW TO STOP SIMULATION WHILE IT IS RUNNING
   Stop all running proccesses by use of the script *clear.sh* from *LinuxRun* dir

## CREDITS ####################################################################
   - *el-gato*

   ## Other contribution:
   - Simple queue's implementation found somewhere in the internet.
   - Solution of other problem with semaphores (in C++ with threads) found in an student online drive
 
______________________________________________________________________________________________________________
*Written in November/December of the 2017*

**DO NOT USE IN COMMERCIAL PURPOSES!!!**

