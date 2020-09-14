#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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
            ...
            break;
        default:
    }
    return N;
}

void manychessmoves(int N, char gamestate[], char goodmove[]) 
{
    for(int i = 0; i < N; ++i)
    {
        start_onemove(i, gamestate, goodmove);
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
