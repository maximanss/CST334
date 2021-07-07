Objectives
1. To develop multi-process application programs
2. To demonstrate the use of pipes as an inter-process communication (IPC) mechanism

I. lab3a.c - this program demonstrates IPC by creating two child process with a pipe in between. 
        It implements shell command: ls | more with one child executes "ls" while the other executes "more".
II. Compile and run lab3b.c - This program demonstrates IPC by creating two child process with a pipe in between.
        One child writes what is in the command line to the upstream of the pipe, while the other child reads
        the data from the downstream of the pipe into the buffer and only 60 characters will be extracted each time.
        Then it (second child) displays each character with space in between from the buffer 
        before getting data from the pipe again.
        The program ends when all the characters have been written to and read from the pipe.
III. lab3c.c - This program demonstrates IPC by creating two child process with a pipe in between. 
        It implements shell command: cat | passwd with one child executes "cat" while the other executes "passwd".
        
run make in Linux to compile the above programs.
