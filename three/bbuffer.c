/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/


#include <stdio.h> 
#include <stdlib.h>  
#include "bbuffer.h"


/*  
* Intialize global variables. Semaphore and mutex.
*/
void initilization() {


    // Semaphores initialization     
    sem_init(&mutex_sem, 0, 1);
    sem_init(&full_sem, 0, BUFFER_SIZE);
    sem_init(&empty_sem, 0, 0);
    
} 


/* *
 * insert_item - thread safe function to insert items to the bounded buffer
 * @param item the value to be inserted
 * @return 0 in case of sucess -1 otherwise
 */
int insert_item(int item, long int id) { // PRODUCER
  
    // Semaphores to check and wait if the buffer is full and
    // ensure exclusive access to the buffer
    sem_wait(&full_sem);
    sem_wait(&mutex_sem);
     
     
    buffer.value[buffer.next_in] = item;
    
    printf("Producer %ld: Inserted item %d into buffer index %d\n", id, item, buffer.next_in);
       
    buffer.next_in = (buffer.next_in + 1) % BUFFER_SIZE;
        

    sem_post(&mutex_sem);   
    sem_post(&empty_sem);
    
    return 0;
}

/**
 * remove_item - thread safe function to remove items to the bounded buffer
 * @param item the address of the variable that the removed value will be written
 * @return 0 in case of sucess -1 otherwise
 */
int remove_item(int *item, long int id) { // CONSUMER
    
    // Semaphores to check and wait if the buffer is empty and
    // ensure exclusive access to the buffer
    sem_wait(&empty_sem);
	sem_wait(&mutex_sem);

         
    *item = buffer.value[buffer.next_out];
    buffer.value[buffer.next_out] = -1;    
    
    
    printf("Consumer %ld: Removed item %d from buffer index %d\n", id, *item, buffer.next_out);
       
    buffer.next_out = (buffer.next_out + 1) % BUFFER_SIZE;
        

    sem_post(&mutex_sem);
	sem_post(&full_sem);
    
    return 0;
}

/**
 * producer - will iterate PRODUCER_ITERATION times and call the corresponding
 * function to insert an integer to the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple producer threads
 * @return nothing
 */
void * producer(void *param) {

    int item, i;
    long int id = (long int)param;

    printf("Producer %d: Started\n", id);
    i = PRODUCER_ITERATIONS;
    while (i--) {
        sleep(rand() % 3);

        item = rand() % 10000;
        if (insert_item(item, id))
            printf("Error while inserting to buffer\n");
    }

    pthread_exit(0);
}

/**
 * consumer - will iterate CONSUMER_ITERATION times and call the corresponding
 * function to remove an integer from the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple consumer threads
 * @return nothing
 */
void * consumer(void *param) {

    int item, i;
    long int id = (long int)param;

    printf("Consumer %d: Started\n", id);
    i = CONSUMER_ITERATIONS;
    while (i--) {
    	sleep(rand() % 3);
    
    	if (remove_item(&item, id))
    	    printf("Error while removing from buffer\n");
    }

    pthread_exit(0);
}
