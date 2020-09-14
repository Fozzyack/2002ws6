#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
        case 0:
            printf("child pid=%i\n", getpid());
            //...
            sleep(4);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }  
    return pid;
}

void manychessmoves(int N, char gamestate[], char goodmove[]) 
{
    for(int i = 0; i < N; ++i)
    {
        int pid = start_onemove(i, gamestate, goodmove);

        if(pid < 0) {
            break;
        }
        wait(&status);
        printf("pid=%i has terminated\n", pid);
    }
}

int main(int argc, char *argv[])
{
    if(argc != 4) {
//error .....
        exit(EXIT_FAILURE);
    }

    int ninstances      = atoi(argv[1]);
//gamestate is argv[2]
//goodmove is argv[3]

    manychessmoves(ninstances, argv[2], argv[3]);
    
    
    exit(EXIT_SUCCESS);
}
