/** Name: Max Halbert
    Date: 3/31/2020
    Tilte: queue_test.c
    Description: The program is to test the data structure of node and fifo queue        
**/
#include <stdio.h>
#include "queue.h"
#include "node.h"

struct queue *q;

int main(void)   {

    q = queue_create();
    
    //testing
    printf("queue is created\n");

    enqueue(q, 99);
    enqueue(q, 201);
    enqueue(q, 1);
    enqueue(q, 22);
    enqueue(q, 33);
    enqueue(q, 69);
    enqueue(q, 21);
    enqueue(q, 2);

    printf("Here are the top %d integers:\n", queue_length(q));
    printf("Content of the queue as follows.\n");
    queue_traverse(q);

    printf("\n");
    printf("Dequeue the first 4\n");
    printf("\n");

    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);

    printf("Here are the top %d integers:\n", queue_length(q));
    printf("Content of the queue as follows.\n");
    queue_traverse(q);

    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    
    printf("\n");
    printf("Number of nodes left in queue: %d\n", queue_length(q));
    printf("Content of the queue as follows.\n");
    queue_traverse(q);
    
    enqueue(q, 100);
    printf("\n");
    printf("Number of nodes left in queue: %d\n", queue_length(q));
    printf("Content of the queue as follows.\n");
    queue_traverse(q);
    
    queue_destroy(q);

    return 0;
}