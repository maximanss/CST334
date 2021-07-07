Objectives
1. To use semaphores for synchronization
2. To develop a C program to solve the producer – consumer problem

a. threadSync.c - a simple schronization program.

b. threadSync2.c - The program solves the problem of prodcuer and consumer.

        Producers are threads that will produce an alphabet and store it in the buffer.
        
        Consumers are threads that will consumes an alphabet producd by the producer by getting it from the buffer.
        
        The synchronization of putting and getting alphabets to the buffer is achieved by using three semaphores: empty, full and mutex.
        
        empty and full semaphores are used to keep track of available slots and items in buffer.
        
        mutex is used to lock the critical section that will be updated by the producers and consumers.
        
        For testing purpose, each thread will display thread number and its produced or consumed item.
        
        Also the producers and consumers threads will sleep at a small random time to show the sychronization between threads.
        
To compile the programs on Linux using Makefile.
