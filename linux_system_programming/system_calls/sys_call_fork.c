#include <stdio.h>
#include <unistd.h> 

// resources which the child process inherits from the parent process: 
//  * stack, heap, data and text segements 
//  * open file descriptors 
//
// why would you use fork() and exec()? e.g. network server serving incoming client requests and 
// creating new child processes for each client request so that it can continue to accept new 
// requests. 
//
// why would fork() fail? 
//  - resource limit on no of processes has been hit
//
// which executes first after fork()? 
//  - this is indeterministic as to if parent or child process will execute first. 
//
//

int main() 
{ 
    pid_t pid = fork();
   
    if (pid == 0) 
        printf("child process\n"); 
    else if (pid == -1) 
        printf("error\n"); 
    else 
        printf("parent process\n"); 

    return 0; 
} 
