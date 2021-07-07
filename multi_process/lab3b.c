/** Name: Max Halbert
    Date: 3/23/2020
    Tilte: Lab 3 step 2 (lab3b.c)
    Description: The program demonstrates IPC by creating two child process with a pipe in between.
        One child writes what is in the command line to the upstream of the pipe, while the other child reads
        the data from the downstream of the pipe into the buffer and only 60 characters will be extracted each time.
        Then it (second child) displays each character with space in between from the buffer 
        before getting data from the pipe again.
        The program ends when all the characters have been written to and read from the pipe.
        
**/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main(int argc,char *argv[])
{
    int fds[2];     // file descriptors for the pipe
    char buff[60];  // only 60 characters can be stored into the buffer 
    int count;
    int i;
    pipe(fds);  // creating a pipe
    
    /*child 1 */
    if (fork()==0)
    {
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        close(fds[0]);
        
        // write all the arguments to the pipe
        for(i=0;i<argc;i++)
        {
            write(fds[1],argv[i],strlen(argv[i]));  // writes the argument to the upstream of the pipe
        }
        exit(0);
    }
    
    /*child 2 */
    else if(fork()==0)
    {
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        // only maximum of 60 bytes will be read each time, until all read
        while((count=read(fds[0],buff,60))>0)
        {
            for(i=0;i<count;i++)
            {   
                write(1,buff+i,1);  // display 1 byte from the buffer
                write(1," ",1);     // then write a space
            }
            printf("\n"); // display a next line
        }
        exit(0);
    }
    else
    {
        /*parent closes both ends of the pipe and wait for children to complete*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}