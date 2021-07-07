# Author: Max Halbert
# Date: 4/13/2020
# Makefile for lab6

all: threadSync2 threadSync

threadSync2: threadSync2.c
	gcc -o threadSync2 threadSync2.c -pthread -Wall 
	
threadSync:	threadSync.c
	gcc -o threadSync threadSync.c -pthread -Wall
	
clean:
	rm -f threadSync2 threadSync