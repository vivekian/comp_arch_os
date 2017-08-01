#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 

int main()
{
   int fd = open("a.txt", O_WRONLY | O_CREAT, 0644); 
   int x = 23; 
   int rc = fork(); 

   if (rc < 0) { 
       printf("unable to fork\n"); 
       exit(1); 
   } 
   else if (rc == 0) { 
       x = 42;
       char buffer[6] = "child"; 
       write(fd, buffer, 6);  
       printf("child process: %d\n", getpid()); 
       printf("value of x: %d\n", x); 
       close(fd); 
   }
   else { 
       char buffer[7] = "parent"; 
       write(fd, buffer, 7); 
       int wc = wait(NULL);
       printf("parent process: %d, child: %d, %d\n", getpid(), rc, wc); 
       printf("value of x: %d\n", x); 
       close(fd); 
   }

   return 0; 
}
