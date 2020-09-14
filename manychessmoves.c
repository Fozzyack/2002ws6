#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int timetaken       = 0;
int start_onemove(int N, char gamestate[], char goodmove[])
{
    printf("./goodchessmove %s %s-%i\n", gamestate, goodmove, N);
    int pid     = fork();
    switch (pid)
    {
        case -1: 
            printf("cannot fork");
            exit(EXIT_FAILURE);
            break;
        case 0: {
            char filename[100];
            sprintf(filename,"%s-%i", goodmove, N);
            printf("child pid=%i\n", getpid());
            //...
            execl("./goodchessmove", "goodchessmove", gamestate, goodmove, NULL);
            exit(EXIT_SUCCESS);
            break;
        }
        default:
            break;
    }  
    return pid;
}
int numberOfCores(int cores) {return cores;}
void manychessmoves(int N, char gamestate[], char goodmove[], int cores) 
{
    int ncores          = numberOfCores(cores);
    int nstarted        = 0;
    int nrunning        = 0;
    int nfinished       = 0;
    int pid, status;

    while(nfinished < N) {
        while(nrunning < ncores && nstarted < N) {
            pid = start_onemove(nfinished, gamestate, goodmove);

            if(pid < 0) {
                break;
            }

            printf("Parent waits for pid=%i\n", pid);
            ++nstarted;
            ++nrunning;
            timetaken += 5;
        }

        if((pid = wait(&status)) > 0)
        {
            ++nfinished;
            --nrunning;
            printf("pid=%i has terminated with status=%i\n", pid, status);
        }
    }
    
}

int main(int argc, char *argv[])
{
    if(argc != 5) {
//error .....
        exit(EXIT_FAILURE);
    }

    int ninstances      = atoi(argv[1]);
    int cores           =atoi(argv[4]);
//gamestate is argv[2]
//goodmove is argv[3]

    manychessmoves(ninstances, argv[2], argv[3], cores);
    printf("timetaken %i\n", timetaken);
    
    
    exit(EXIT_SUCCESS);
}
