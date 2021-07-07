/** Name: Max Halbert
    Date: 3/23/2020
    Tilte: Lab 3 step 1 (lab3a.c)
    Description: The program demonstrates IPC by creating two child process with a pipe in between. 
        It implements shell command: ls | more with one child executes "ls" while the other executes "more".
**/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//main
int main() 
{
    int fds[2];  // file descriptor
    pipe(fds);  // creating a pipe 
    
    /*child 1 */
    if (fork() == 0)
    {
        dup2(fds[0], 0);  // duplicates downstream into stdin
        close(fds[1]);
        execlp("more", "more", NULL);  // execute the more command 
    }
    
    /*child 2 */
    else if (fork() == 0) 
    {
        dup2(fds[1], 1);  // duplicates upstream into stdout
        close(fds[0]);
        execlp("ls", "ls", NULL);  // execute the ls command 
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