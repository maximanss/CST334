/** Name: Max Halbert
    Date: 3/30/2020
    Tilte:queue.c
    Description: Functions to create and manage a FIFO queue
**/

#include "node.h"
#include "queue.h"

// Function to create a FIFO queue
struct queue* queue_create() 
{ 
    struct queue* queue = (struct queue*) malloc(sizeof(struct queue)); 
    queue->capacity = DEFAULT_SIZE; 
    queue->front = NULL;
    queue->rear = NULL;  // This is important, see the enqueue 
    queue->size = 0;  
    return queue; 
}

// Function to change the capacity of the queue
void queue_set_size(struct queue* q, int max)
{
    q->capacity = max;
}


// Function to check if the queue is full 
int isFull(struct queue* queue) 
{  
    return (queue->size == queue->capacity);  
} 
  
// Function to check if the queue is empty 
int isEmpty(struct queue* queue) 
{  
    return (queue->size == 0); 
} 
  
// Function to add an item to the queue.   
// It changes rear and size
// Returns 1 if it succeeds otherwise 0
int enqueue(struct queue* queue, int item) 
{ 
    // If queue is full, fail to add the item
    if (isFull(queue)) 
        return 0;   // fail
    
    // Create a node to store the item
    // append the node to end of the queue
    struct node* newnode = node_create(item);
    if (isEmpty(queue))
    {   // The queue is empty
        queue->front = newnode; // set front to the new node
        queue->rear = newnode;  // set rear to the new node
    }
    else
    {   // The queue is not empty
        struct node* rearnode = queue->rear;
        node_set_nextptr(rearnode, newnode); // set the next pointer of rear node
        queue->rear = newnode;  // update the rear pointer to new node
    }
    
    queue->size++; // increment the length of the queue
    
    //printf("%d enqueued to queue\n", item); // debugging 
    return 1;  // success
} 
  
// Function to remove first item from the queue.  
// It changes the front and size
// Returns 1 if succeed otherwise 0 
int dequeue(struct queue* queue) 
{ 
    // queue is empty then fail
    if (isEmpty(queue)) 
        return 0;
    
    // set the front pointer to next node 
    struct node* frontnode = queue->front;
    queue->front = node_get_nextptr(frontnode); 
    node_destroy(frontnode); // remove the old front node
    
    queue->size--;  // decrement the length of the queue
    
    // if queue is empty, set front and rear pointer to NULL
    if (queue->size == 0)
    {
        queue->front = NULL;
        queue->rear = NULL;
    }
    
    return 1; // success
} 

// Function to search the queue for whether the item exsists
// return 1 if found otherwise 0
int queue_search(struct queue* q, int item)
{
    // Start searching from the front of the queue
    struct node* currPtr;
    currPtr = q->front;
    
    // Search until end of the queue
    while (currPtr != NULL)
    {
        if(node_get_data(currPtr) == item)
            return 1;  // found the item
        else
            currPtr = node_get_nextptr(currPtr);  // next node
    }
    return 0;   // Not found
}

// Function to traverse through the queue
// and print out the item
void queue_traverse(struct queue* q)
{
    int i = 0;
    struct node* currPtr;
    currPtr = q->front;
    while (currPtr != NULL)
    {
        printf("%d %d\n", i, node_get_data(currPtr));
        currPtr = node_get_nextptr(currPtr);
        i++;
    }
}

void queue_destroy(struct queue *q)
{
    struct node* currPtr;
    struct node* nextPtr;  
    currPtr = q->front;
    while(currPtr != NULL)
    {
        nextPtr = node_get_nextptr(currPtr);
        node_destroy(currPtr);
        currPtr = nextPtr;
    }
    free(q);
}

// this function returns the size of the queue 
int queue_length(struct queue* q)
{
    return q->size;
}



