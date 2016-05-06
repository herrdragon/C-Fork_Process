// process.c
/******************************************************************************/
/* PROGRAMMER:  Luis M. Herrnsdorf  
	 ID: 5481644
	 CLASS:       COP4338 U03   TT 7:50
	 INSTRUCTOR:  William Feild
	 ASSIGNMENT:  #6.   DUE Thursday 4/28
*/
/*DESCRIPTION: header file contains common constants, declarations, prototypes 
* & type declarations that are used by readDates.c, writeDates.c, filterDates.c
*/
/* 
	CERTIFICATION: I hereby certify that this collective work is my own and none
					of it is the work of any other person or entity.
						Luis Herrnsdorf
*/
/* DESCRIPTION: Program that accept a number of arguments from the command-line 
– maximum of 7 – each a unique integer between 0-9. The program (parent process) 
will request shared memory for these integers, and spawn child process equal to 
the number of arguments. Upon completion of all children, the parent will 
acknowledge said completion (and exit codes), display the current state of the 
shared memory, detach the shared memory, remove the shared memory, and then 
exit.  Child processes display the shared memory and private memory (unique ID) 
upon initiation. Each child will display the current state of the shared memory 
and their unique ID. Next each child will locate the array element (index) 
associated with their unique ID and then multiply that array element by their 
unique ID, storing the result in the array element. Each child will then display
the current state of the shared memory and exit.
*/

/* SPECIFICATIONS: Appropriate error handling should be included for the 
spawning of processes and for each step of the shared memory process. Use of 
MakeFile will be required for this assignment.
*/

/* Input: Maximum of 7 numbers – each a unique integer between 0-9. */

/* COMPILATION: Makefile: make */

/* EXECUTE: ./fork.out 1 2 3 4 5 6 7 */

/* 
  CERTIFICATION: I hereby certify that this collective work is my own and none
                 of it is the work of any other person or entity.
                    Luis Herrnsdorf
*/

/* START PSEUDO CODE
int main(int argc, char *argv[]) {
    if (!checkArgs())
        return 1;
    if (!validateInput())
		return 1;

    getShareMeme();
    if (pid == 0)
		for(numberOfArgs)
	    	childProcess();
    parentProcess();

    return 0;
}
 END PSEUDO CODE */
/******************************************************************************/

#include <stdio.h>
#include <sys/shm.h> // for shmget(), shmat(), IPC_PRIVATE
#include <unistd.h>  // for fork()
#include <stdlib.h>  // exit()
#include "header.h"  // definition for types and functions

int main(int argc, char *argv[]) {
	// check the right amount of parameters
	if(!checkArgs(MINNUMS, MAXNUMS, argc))
		return FALSE;

	int INPUT = argc - 1; // get the number of parameters passed
	int ids[INPUT]; // create an int array of size of parameters passed

	// check for valid parameters
	if(!checkInputs(INPUT, argc, ids, argv))
		return FALSE;
	
	// then if pass all validations...
	int ShmID; 
	int *ShmPTR;
	pid_t pid;  
	int status;
	int chidlPID;
	
	ShmID = shmget(IPC_PRIVATE, INPUT*sizeof(int), IPC_CREAT | 0666);
	if (ShmID < 0) {
		printf("%s\n","*** shmget error (Parent) ***");
		return ERRORFOUND;
	}

	printf("%s ", "Parent has received a shared memory of");
	printf("%d %s\n", INPUT,"integers...");
	
	ShmPTR = (int *) shmat(ShmID, NULL, 0);
	if ((long) ShmPTR == -1) {
		printf("%s\n","*** shmat error (Parent) ***");
		return ERRORFOUND;
	}

	printf("%s\n", "Parent has attached the shared memory...");
	printf("%s","Parent has filled in shared memory with: ");
	int i;
	for (i = 0; i < INPUT; i++) {
		ShmPTR[i] = ids[i];
	}
	printShrMem(ShmPTR, INPUT);

	printf("%s\n","Parent is about to fork a child process...");
	int childId;
	for(childId = 1; childId <= INPUT; childId++) {
		pid = fork();
		if (pid < 0) {
			printf("%s\n","*** fork error (Parent) ***");
			return ERRORFOUND;
		}
		else if (pid == 0) {
			ChildProcess(ShmPTR, INPUT, childId);
			exit(0);
		}
	}

	ParentProcess(ShmPTR, ShmID, INPUT, status, chidlPID);

	return NOERRORS;
}
