#include <iostream> 
#include <semaphore.h> 
#include <thread> 

sem_t *s; 
int cnt=0; 

void thread1() 
{
   int ret; 
   ret = sem_wait(s);
   ++cnt; 
   sem_post(s); 
}

void thread2() 
{ 
    int ret; 
    ret = sem_wait(s);
    ++cnt; 
    sem_post(s);
}

int main() 
{
   s = sem_open("test123", O_CREAT); 
   
   std::thread t1(thread1); 
   std::thread t2(thread2); 

   t1.join(); 
   t2.join();

   std::cout << cnt << std::endl; 
   sem_close(s);

   return 0;
}
