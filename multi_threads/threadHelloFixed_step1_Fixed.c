/** Name: Max Halbert
    Date: 4/6/2020
    Tilte: Lab 5 thread program (threadHelloFixed_step1_Fixed.c)
    Description: This is the thread program 
        to show how to create threads (bug fixed program from threadHello.c)
**/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10     // 10 threads to create
pthread_t threads[NTHREADS];    // store the thread id
int threads_arg[NTHREADS];      // thread safe space for each thread

int main() 
{
    int i;
    for (i = 0; i < NTHREADS; i++)
    {
        threads_arg[i] = i;     // thread safe number to each thread
        if (pthread_create(&threads[i], NULL, go, &threads_arg[i]))
        {
            // computer system failed to create thread
            printf("failed thread create!\n");
            return 0;
        }
    }
    for (i = 0; i < NTHREADS; i++) 
    {        
        pthread_join(threads[i],NULL);
        printf("Thread %d returned\n", i);
    }
    printf("Main thread done.\n");
    return 0;
}

// thread function
void *go(void *arg) 
{
    printf("Hello from thread %u with iteration %d\n", (int)pthread_self(), *(int *)arg);
    return 0;
}