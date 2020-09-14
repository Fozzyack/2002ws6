//  A STANDARD SET OF HEADER FILES REQUIRED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>                  // provides MAXPATHLEN

#include <sys/wait.h>

//  A FAKE LIBRARY-FUNCTION
int numberOfCores(void) { return 2; }

int start_onemove(int N, char gamestate[], char goodmove[])
{
    int pid     = fork();

//  fork()-ING NEW PROCESSES
    switch (pid) {

//  ACCOUNT FOR fork() FAILING
    case -1:
        break;

//  CHILD PROCESS NEEDS TO RUN THE goodchessmove PROGRAM
    case  0: {

//  FORMAT EACH OUTPUT FILE'S NAME - WE DO NOT NEED TO OPEN/CREATE IT
        char outputfile[MAXPATHLEN];
        sprintf(outputfile, "%s-%i", goodmove, N+1);

//  OVERWRITE CURRENT PROCESS WITH NEW PROGRAM
        execl(  "./goodchessmove",      // on-disk location of program
                "goodchessmove",        // its argv[0]
                gamestate,              // its argv[1]
                outputfile,             // its argv[2]
                NULL
            );

//  ACCOUNT FOR THE execl() FAILING
        exit(EXIT_FAILURE);
        break;
    }

//  PARENT PROCESS
    default:
        printf("parent creates child pid=%i\n", pid);
        break;
    }
    return pid;
}

int manychessmoves(int ninstances, char gamestate[], char goodmove[])
{
//  WELL-CHOSEN IDENTIFIER NAMES MAKE THE LOGIC EASIER TO READ
    int ncores          = numberOfCores();
    int nstarted        = 0;
    int nrunning        = 0;

    int result          = 0;            // 0=success, 1=any_failures
    int pid, status;

//  2 NESTED WHILE STATEMENTS SUPPORT THE LOGIC, BUT THERE MAY BE A SIMPLER WAY
    while(nstarted < ninstances && result == 0) {
        while(nrunning < ncores && nstarted < ninstances && result == 0) {

            if(start_onemove(nstarted, gamestate, goodmove) > 0) {
                ++nstarted;
                ++nrunning;
            }
        }                               // inner while loop

//  PARENT PROCESS WAITS FOR 1 PROCESS, THEN KEEPS CORES BUSY
        if(nrunning > 0 && result == 0) {
            if( (pid = wait(&status)) > 0) {
                printf("child pid=%i terminated with status=%i\n\n", pid, status);
                --nrunning;

//  ENSURE THAT TERMINATING CHILD PROCESS WAS SUCCESSFUL
                if(status != 0) {
                    result      = 1;
                }
            }
        }
    }                                   // outer while loop

//  WHEN ALL CHILDREN HAVE EVENTUALLY STARTED, OR AN ERROR IS DETECTED,
//  WE STILL NEED TO wait() FOR ANY REMAINING PROCESSES
    while( (pid = wait(&status)) > 0) {
        printf("child pid=%i terminated with status=%i\n\n", pid, status);
        if(status != 0) {
            result      = 1;
        }
    }
    return result;                      // 0=success, 1=any_failures
}

//  main() CHECKS ARGUMENTS, CALLS ANOTHER FUNCTION TO DO THE REAL WORK
int main(int argc, char *argv[])
{
    if(argc != 4) {
        fprintf(stderr, "Usage: .....\n");
        return 1;
    }
    else {
        int ninstances  = atoi(argv[1]);

        return manychessmoves( ninstances, argv[2], argv[3] );
    }
}
