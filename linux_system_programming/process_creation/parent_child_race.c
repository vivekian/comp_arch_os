#include <stdio.h> 
#include <sys/wait.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 

int main(int argc, char *argv[])
{
    int numChildren, j;
    pid_t childPid;

    sscanf(argv[1], "%d", &numChildren);  

    setbuf(stdout, NULL);
    
    for (j = 0; j < numChildren; j++) {
        switch (childPid = fork()) {
        case -1:
            printf("error\n"); 
        case 0:
            printf("%d child\n", j);
            _exit(EXIT_SUCCESS);
        default:
            printf("%d parent\n", j);
            wait(NULL);
            break;
        } 
    }

    exit(EXIT_SUCCESS);
}
