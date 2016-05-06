// header.h
/******************************************************************************/
/* PROGRAMMER:  Luis M. Herrnsdorf  
   ID: 5481644
   CLASS:       COP4338 U03   TT 7:50
   INSTRUCTOR:  William Feild
   ASSIGNMENT:  #6.   DUE Thursday 4/28
*/
/*DESCRIPTION: header file contains common constants, declarations, prototypes 
* & type declarations that are used by process.c and memfunc.c
*/
/* 
  CERTIFICATION: I hereby certify that this collective work is my own and none
                 of it is the work of any other person or entity.
                    Luis Herrnsdorf
*/
/******************************************************************************/
#define ERRORFOUND 1 // found one or more errors
#define NOERRORS 0   // no errors found
#define MAXNUMS 8    // used to control maximum number of inputs
#define MINNUMS 2    // used to control minimum number of inputs
#define MINVAL 0     // used to control minimum value of inputs
#define MAXVAL 9     // used to control maximum value of inputs
#define FALSE 0      // used to return 0
#define TRUE 1       // used to return 1

/******************************************************************************/
//   FUNCTIONS for process.c
/******************************************************************************/
void ChildProcess(int[], int, int);

void ParentProcess(int[], int, int, int, int);

int checkArgs(int, int, int);

int checkInputs(int, int, int[], char *[]);

void printShrMem(int[], int);
