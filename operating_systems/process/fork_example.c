#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 

int main()
{
   int rc = fork(); 

   if (rc < 0) { 
       printf("unable to fork\n"); 
       exit(1); 
   } 
   else if (rc == 0) { 
       printf("child process: %d\n", getpid()); 
   }
   else { 
       printf("parent process: %d\n", getpid()); 
   }

   return 0; 
}
