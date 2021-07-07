/**
    Name: Max Halbert
    Date: 4/13/2020
    Title: threadSync2.c
    Description: The program solves the problem of prodcuer and consumer. 
        Producers are threads that will produce an alphabet and store it in the buffer.
        Consumers are threads that will consumes an alphabet producd by the producer by getting it from the buffer.
        The synchronization of putting and getting alphabets to the buffer is achieved by
        using three semaphores: empty, full and mutex.
        empty and full semaphores are used to keep track of available slots and items in buffer.
        mutex is used to lock the critical section that will be updated by the producers and consumers.
        For testing purpose, each thread will display thread number and its produced or consumed item.
        Also the producers and consumers threads will sleep at a small random time to show the sychronization between threads.
        
    Note: This program allows multiple producer and multiple consumer by changing NP_THREADS and NC_THREADS values
        Also buffer size can change in runtime by entering the size of buffer as an argument after the executables although 
        default is 26.
        For Example: ./threadSync2 10   means change buffer size is 10
        
**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h>
#include <time.h>
#include <assert.h>

sem_t empty;        // semaphore to show empty spaces in the buffer
sem_t full;         // semaphore to show number of items in the buffer
sem_t mutex;        // lock for critical section

#define SLEEP 1    // if SLEEP is 1 both producers and customers will sleep before put or get, no sleep if SLEEP is 0
#define NP_THREADS 1    // number of producer
#define NC_THREADS 1   // number of consumer
#define DEFAULT_BUFF_SIZE 26    // size of buffer

pthread_t pthreads[NP_THREADS];  // array of producer threads
pthread_t cthreads[NC_THREADS];  // array of consumer threads

int quantity = 26;              // quantity of items to be produced and consumed, 30 if no changed
char* buffer;                   // buffer for storing items, can store up to 26 items
int buff_size = DEFAULT_BUFF_SIZE;
int product_num = 0;                   // the product is product_num + 'A', and can be up to 'Z'
int p_iterator = 0;             // both producer and consumer start from the top of buffer
int c_iterator = 0;

int pd_count = 0;       // counter for number of items produced
int cm_count = 0;       // counter for number of items consumed

// Prototypes of functions
void* producer(void* arg);  // producer function
void *consumer(void *arg);  // consumer function
char put();
char get();

// Function to produce an item and put into the buffer
// Return the item produced, zero means no more items produced
char put()
{
    char item;  // item to be produced
    
    sem_wait(&empty);   // wait for empty slot in buffer
    sem_wait(&mutex);   // wait to enter critical section
        
    // Critical section to produce an item and store in buffer
    if (pd_count < quantity)    // check if another producer thread reach the quantity
    {
       item = product_num + 'A';
       product_num = (product_num + 1) % 26;   // product can only be from 'A' to 'Z'
       buffer[p_iterator] = item;
       p_iterator = (p_iterator + 1) % buff_size;  // wrap around the buffer
       pd_count++;         // increment the production count
       
    }
    else
        item = 0;       // production is done
    
    sem_post(&mutex);   // release lock
    sem_post(&full);    // signal consumer for available item to consume
    
    return item;
}

// Function to get an item from the buffer
// Return the item consumed, zero means no more items consumed
char get()
{
    char item;      // storage for item from buffer
    
    sem_wait(&full);    // wait for item available in buffer
    sem_wait(&mutex);   // wait to enter the critical section (only 1 thread at one time)
        
    // Critical Section to consume an item from the buffer
    if(cm_count < quantity)
    {
        item = buffer[c_iterator];
        c_iterator = (c_iterator + 1) % buff_size;
        cm_count++;
        
    }
    else
        item = 0;       // no more items
    
    sem_post(&mutex);   // release the lock
    sem_post(&empty);   // signal producer for an available space
    
    return item;
        
}


// Function for producer thread
// Once necessary semaphores are acquired, it will produce an item and store it in buffer
// Semaphores will be released after item is produced
// Thread number and item will be displayed
// Thread ends when the production quantity is reached
// For testing purpose: thread will sleep for 0-3 seconds after each production
void* producer(void* arg) 
{ 
    char produced;
    do
    {
        if (SLEEP)
            sleep(rand()%4);    // sleep up to 3 seconds for testing purpose
        
        produced = put();
        
        if(produced)
        {
            printf("Producer %lu produced %c\n", (size_t)arg, produced);
            
        }
        
    } while(produced);    // loop back since still producing
    
    return 0;
} 

// Function for consumer thread
// Once necessary semaphores are acquired, it will consume an item from the buffer
// Semaphores will be released after item is consumed
// Thread number and item will be displayed
// Thread ends when the consumption quantity is matched with production quantity
// For testing purpose: thread will sleep for 0-3 seconds after each consumption
void *consumer(void *arg)
{
    char consumed;        // consume item
    do 
    {
        if (SLEEP)
            sleep(rand()%4);    // sleep up to 3 seconds for testing purpose
        
        consumed = get();
        
        if(consumed)
        {
            printf("\tConsumer %lu consumed %c\n", (size_t)arg, consumed);
            
        }
    } while(consumed);       // still consume
    
    return 0;
}

// Main function to create threads for producers and consumers
// exit only when all the threads exit
int main(int argc, char *arg[]) 
{ 
    // user can change the buffer size used in produce and consume
    if (argc > 1)
    {
        // only change the buffer size if it is positive number
        int q = atoi(arg[1]);
        if (q > 0) 
            buff_size = q;
    }
        
    buffer = (char *)malloc(buff_size * sizeof(char));  // allocate memory for buffer
    
    
    sem_init(&empty, 0, buff_size); // initialize available slots to the buffer size
    sem_init(&full, 0, 0);  // nothing available in the buffer
    sem_init(&mutex,0,1); //initialize a binary semaphore with value 1
    
    srand(time(0));     // initialize random generator
    
    static int i;
    int rc = 1;
    for (i = 0; i < NP_THREADS; i++)
    {   // create producer threads     
        rc = pthread_create(&pthreads[i], NULL, producer, (void *)(size_t)i); //the last arg is the arg of producer
        assert(rc == 0);
    }
    for(i = 0; i < NC_THREADS; i++)
    {   // create consumer threads
        rc = pthread_create(&cthreads[i], NULL, consumer, (void *)(size_t)i); //the last arg is the arg of consumer
        assert(rc == 0);
    }
    
    // wait for all the producer and consumer threads are done
    for (i = 0; i < NC_THREADS; i++)
    {
        pthread_join(cthreads[i],NULL);
        printf("Consumer Thread %d returned \n", i);
    }
    for (i = 0; i < NP_THREADS; i++) 
    {
        pthread_join(pthreads[i],NULL);
        printf("Producer Thread %d returned \n", i);
    }
    
    printf("Main thread done.\n");
    
    sem_destroy(&empty); //drop the semaphone when finished.
    sem_destroy(&full); //drop the semaphone when finished.
    sem_destroy(&mutex); //drop the semaphone when finished.
    
    free(buffer);       // free the allocated memory
    
    return 0; 
} 







