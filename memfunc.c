// memfunc.c
/******************************************************************************/
/* PROGRAMMER:  Miguel Herrnsdorf */
/*DESCRIPTION: functions used by process.c
*/
/* 
  CERTIFICATION: I hereby certify that this collective work is my own and none
                 of it is the work of any other person or entity.
                    Luis Herrnsdorf
*/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>  // for exit(), wait(), atoi()
#include <unistd.h>  // for getpid()
#include <ctype.h>   // for isdigit()
#include <sys/shm.h> // for shmget(), shmat(), IPC_PRIVATE
#include "header.h"  // definition for types and functions

/******************************************************************************/
/*
* Function: checkArgs
* ------------------------
* Check the minimum and maximun number of arguments.
*
* arg: int MININP: minimum number allowed, int MAXINP: maximum number alloed,
* int argc: total number of arguments passed.
* return: FALSE if argc is not within the range, TRUE otherwise
* side effects: none.
*/
int checkArgs(int MININP, int MAXINP, int argc) {
    if (argc < MININP || argc > MAXINP) {
        printf("%s\n", "Input must be at least 1 but no more than 7 numbers");
        return FALSE;
    }
    return TRUE;
}
/******************************************************************************/
/*
* Function: checkInputs
* ------------------------
* Validate the arguments passed to the program.
*
* arg: int INPUT: actual number of arguments to check, int argc:  total number 
* of arguments passed, int[] ids: array of child unique identifyer, int *argcv[]
* : pointer to array of the arguemts passed.
* return: FALSE if inputs are not valid or outside the range. TRUE otherwise.
* side effects: none.
*/
int checkInputs(int INPUT, int argc, int ids[], char *argv[]) {
    int i = 0;
    int j = 0;

    for(i = 0; i < INPUT; i++) {
        if(isdigit(*argv[i+1])) // check all inputs are numbers
            ids[i] = atoi((argv[i+1])); // turn all chars to ints
        else {
            printf("%s\n", "Input must be a number between 0 - 9");
            return FALSE;
        }
    }

    if(argc > 2) { // check only if there is more than 1 argument
        for (i = 0; i < INPUT; i++) {
            for(j = i+1; j < INPUT; j++) {
                if(ids[i] == ids[j]) { // check for duplicate entries
                    printf("%s\n", "Each input must be unique");
                    return FALSE;
                }
            }
        }
    }

    for (i = 0; i < INPUT; i++) {
        if(ids[i] < MINVAL || ids[i] > MAXVAL) { // check for input range
            printf("%s\n", "Input must be between 0 - 9");
            return FALSE;
        }
    }

    return TRUE;
}
/******************************************************************************/
/*
* Function: printShrMem
* ------------------------
* Print the content of the share memory.
*
* arg: int ShmPTR[]: pointer to the share memory, int INPUT: actual number of 
* arguments to check.
* return: void
* side effects: none.
*/
void printShrMem(int ShmPTR[], int INPUT) {
    int i;
    for (i = 0; i < INPUT; i++) {
        printf("%d ", ShmPTR[i]);
    }
    printf("%s\n", "");
}
/******************************************************************************/
/*
* Function: ChildProcess
* ------------------------
* Display child actions and modify the correspondent child share memory.
*
* arg: int ShmPTR[]: pointer to the share memory, int INPUT: actual number of 
* arguments to check, int uid: child unique id.
* return: void
* side effects: modify share memory.
*/
void ChildProcess(int ShmPTR[], int INPUT, int uid) {
    printf("%s %d %s\n", "   Child",uid,"process started");
    printf("%s %d %s","   Child", uid ,"has reach in shared memory:");
    printShrMem(ShmPTR, INPUT);
    ShmPTR[uid-1] = ShmPTR[uid-1] * uid;
    printf("%s %d\n", "   My unique child ID is:",uid);
    printf("%s %d %s %d\n", "   Child", uid ,"PID is:",getpid());
    printf("%s %d %s %d\n", "   Child", uid ,"new memory is:" , ShmPTR[uid-1]);
    printf("%s %d %s", "   Child", uid ,"new shared memory status:");
    printShrMem(ShmPTR, INPUT);
    printf("%s %d %s\n", "   Child", uid ,"is about to exit");
    printf("%s\n", "");
    exit(0);
}
/******************************************************************************/
/*
* Function: ParentProcess
* ------------------------
* Display parent actions, child process termination, detach&remove share memory.
*
* arg: int day, int month, int year.
* return: void
* side effects: detach & remove the share memory .
*/
void ParentProcess(int ShmPTR[], int ShmID, int INPUT, int status, 
                   int chidlPID) {
    int i;
    for (i = 1; i <= INPUT; i++) {
        chidlPID = wait(&status);
        printf("%s","Parent has detected the completion of child with PID ");
        printf("%d\n", chidlPID);
        printf("%s\n", "");
    }

    printf("%s","Parent new shared memory status:");
    printShrMem(ShmPTR, INPUT);

    shmdt((void *) ShmPTR);
    printf("%s\n","Parent has detached its shared memory...");
    shmctl(ShmID, IPC_RMID, NULL);
    printf("%s\n","Parent has removed its shared memory...");
    printf("%s\n","Parent exits...");
}
