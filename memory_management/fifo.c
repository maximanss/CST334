/** Name: Max Halbert
    Date: 3/30/2020
    Tilte: fifo.c
    Description: The program similate the fifo queue for memory management.
        It will allocate a fifo queue with a given size. Then read in the page number from 
        the standard input, if the page number is not in the queue, 
        then the page number will be put into the end of the queue unless it is full.
        If the queue is full, the first one in queue will be removed for the page number.        
**/

#include "queue.h"

int main(int argc, char *argv[])
{
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user
    //printf("Size of queue is %d\n", C_SIZE);  // for debugging
    
    char pageCache[100]; // Cache that holds the input from the standard input

    int totalFaults = 0; // keeps track of the total page faults
    
    // allocate a fifo queue with given size
    struct queue* q = queue_create();
    queue_set_size(q, C_SIZE);
    
    //int ctr = 0;  // for debugging
    
    
    // Read the page number from standard input until the end of the file
    while (fgets(pageCache, 100, stdin))
    {
        // check to see if the first character
        // of the input line is a digit, ignore the line if it is not a digit
        if(pageCache[0] >= '0' && pageCache[0] <= '9')
        {
            int page_num = atoi(pageCache); // convert the input to an integer
            
            // for debugging
            //printf("%d %d\n", ctr, page_num);
            //ctr++;
            
            // check whether the page number is in the queue
            if(!queue_search(q, page_num))
            {
                // not in the queue means "Miss" or "Page Fault"
                // Then store the page number into the queue
                if(!enqueue(q, page_num))
                {
                    // queue is full
                    //printf("Queue is filled up, %d\n", queue_length(q));
                    
                    dequeue(q); // remove the front page number from the queue
                    
                    // Now put the page number into the queue
                    if (!enqueue(q, page_num))
                        printf("Error in the queue!\n");  // for debugging
                }
                totalFaults++;  // increment the page fault count
            }
        }
        
    }

    //printf("Number of access: %d\n", ctr);  // for debugging
    //queue_traverse(q);  // for debugging
    
    printf("%d Total Page Faults\n", totalFaults);
    
    queue_destroy(q);   // free the allocated memory
    
    return 0;

}