Objectives
1. To simulate a basic page replacement algorithm
2. To evaluate the performance, in terms of miss/hit rate, of this algorithm

a. fifo.c - This program similate the fifo queue for memory management.
        It will allocate a fifo queue with a given size. Then read in the page number from 
        the standard input, if the page number is not in the queue, 
        then the page number will be put into the end of the queue unless it is full.
        If the queue is full, the first one in queue will be removed for the page number.
        
b. node.c - Create and Destroy node, which is used in the queue as a page

c. queue.c - Functions to create and manage a FIFO queue

d. queue_test.c - The program is to test the data structure of node and fifo queue
            whether the queue is operated as expected.
            
run make on linux to compile the programs.
