#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/wait.h> 
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
//  - in Linux, there is generally a kernel policy on which to run first - in general this is parent. 
//  - but kernel devs can go with child first too and there is never 100% guarantee on what should be picked. 
//  - /proc/sys/kernel/sched_child_runs_first file can be modified to update this behavior. 
//
// file descriptors between child and parent process are shared even after fork() is called. 
// e.g. if a child process executes and changes file attribute for an open file, then it will 
// be reflected on the parent process. 

int main() 
{
    int istack = 22;
    char template[] = "/tmp/testXXXXXX"; 

    setbuf(stdout, NULL); 
    int fd = mkstemp(template); 

    printf("File offset before fork(): %lld\n", (long long) lseek(fd, 0, SEEK_CUR));

    pid_t pid = fork();
   
    if (pid == 0) { 
        istack *= 3;
        lseek(fd, 100, SEEK_SET); 
        printf("child process, istack=%d\n", istack); 
        _exit(); 
    }
    else if (pid == -1) 
        printf("error\n"); 
    else { 
        // stack data is different between child and parent process 
        printf("parent process, istack=%d\n", istack); 
        // wait for child process to complete execution. 
        wait(NULL);
        printf("File offset after fork() in parent: %lld\n", (long long) lseek(fd, 0, SEEK_CUR));
    } 


    return 0; 
} 
