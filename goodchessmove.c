#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc == 3) {
        printf("\thello from program %s, pid=%i\n", argv[0], getpid() );

        srand( getpid() );              // seed the random number generator
        sleep( rand() % 4 + 1);         // sleep for a random time
        printf("POWER -----end\n\n");
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}
