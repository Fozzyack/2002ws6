#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



void manychessmoves(int N, char gamestate[], char goodmove[]) 
{
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
