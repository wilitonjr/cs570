/*
* Wiliton Abreu Rodrigues 
* Edoras - cssc2301
* SDSU - CS570 (summer 2020)
* REDid: 824508185
*/

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 4   // rounded buffer size

#define PRODUCERS 3  // number of producers
#define CONSUMERS 3  // number of consumers

#define ITERATIONS 30  // number of actions producers/consumers perform 
#define PRODUCER_ITERATIONS (ITERATIONS / PRODUCERS)  //number of actions each producer performs
#define CONSUMER_ITERATIONS (ITERATIONS / CONSUMERS) //number of actions each consumer performs

typedef struct {
    int value[BUFFER_SIZE];
    int next_in, next_out;
} buffer_t;    // struct of bounded buffer


buffer_t buffer;   //global variable: rounded buffer

pthread_t consumer_tid[CONSUMERS], producer_tid[PRODUCERS]; // producer and consumer threads



// Declares semaphores
sem_t mutex_sem, empty_sem, full_sem;


// Declares functions
void * consumer(void *param);
void * producer(void *param);
void initilization();



