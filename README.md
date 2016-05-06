# C-Fork_Process
Program that accept a number of arguments from the command-line – maximum of 7 – each a unique integer between 0-9. The program (parent process) will request shared memory for these integers, and spawn child process equal to the number of arguments. Upon completion of all children, the parent will acknowledge said completion (and exit codes), display the current state of the shared memory, detach the shared memory, remove the shared memory, and then exit.
Child processes display the shared memory and private memory (unique ID) upon initiation. Each child will display the current state of the shared memory and their unique ID. Next each child will locate the array element (index) associated with their unique ID and then multiply that array element by their unique ID, storing the result in the array element. Each child will then display the current state of the shared memory and exit.

To use this program
--------------------
1- On the terminal, navigate to where the files are.

2- Make sure you have all four files (process.c, memfunc.c, header.h, and Makefile) in the same directory.

3- Type “make” and press enter to compile the program.

4- Then type for example “./fork.out 1 2 3" to run the program and fork 3 children.
