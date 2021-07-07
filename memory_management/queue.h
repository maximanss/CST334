/** Name: Max Halbert
    Date: 3/30/2020
    Tilte:queue.h 
    Description: Header file for queue.c
**/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_SIZE	100

struct queue
{
	int capacity;		// maximum capacity of the queue
	int size;			// length of the queue
	struct node* front;	// pointer to first node
	struct node* rear;	// pointer to last node
};

struct queue* queue_create();

void queue_set_size(struct queue* q, int max);

int isEmpty(struct queue* queue);

int enqueue(struct queue* queue, int item);

int dequeue(struct queue* queue); 

int front(struct queue* queue);

int rear(struct queue* queue);

int queue_search(struct queue* q, int item);

void queue_traverse(struct queue* q);

void queue_destroy(struct queue *q);

int queue_length(struct queue* q);