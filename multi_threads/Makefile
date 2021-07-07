#Make file for lab5

all: threadHello_step1 threadHelloFixed_step1_Fixed matrix_multiplication

threadHello_step1:	threadHello_step1.c
	gcc -o threadHello_step1 threadHello_step1.c -pthread -Wall

threadHelloFixed_step1_Fixed:	threadHelloFixed_step1_Fixed.c
	gcc -o threadHelloFixed_step1_Fixed threadHelloFixed_step1_Fixed.c -pthread -Wall
	
matrix_multiplication:	matrix_multiplication.c
	gcc -o matrix_multiplication matrix_multiplication.c -pthread -Wall
	
clean:
	rm -f threadHello_step1 threadHelloFixed_step1_Fixed matrix_multiplication