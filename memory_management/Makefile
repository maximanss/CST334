#Make file for lab4

all: fifo queue_test

fifo:	queue.h queue.c node.h node.c fifo.c
	gcc -o fifo fifo.c queue.c node.c -Wall -Werror

queue_test: queue_test.c queue.c node.c queue.h node.h
	gcc -o queue_test queue_test.c queue.c node.c -Wall -Werror

	
clean:
	rm -f fifo queue_test
	