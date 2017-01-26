// using semaphore as a conditional variable 

#include <semaphore.h> 
#include <iostream> 
#include <thread> 

sem_t *s; 
int cnt = 0;
constexpr int MAX = 100; 

void odd()
{ 
    while (cnt < MAX) { 
        if (cnt % 2) { 
            sem_wait(s);
            std::cout << cnt << "\n" ; 
            std::cout.flush();
            ++cnt;
            sem_post(s);
        }
    }
} 

void even() 
{
    while (cnt < MAX) { 
       if (!(cnt % 2)) {  
            sem_wait(s);
            std::cout << cnt << "\n" ; 
            std::cout.flush(); 
            ++cnt; 
            sem_post(s);
       }
    }
}

int main() 
{ 
    s = sem_open("oddeven", 1); 

    std::thread t1(odd); 
    std::thread t2(even);

    t1.join();
    t2.join();

    sem_close(s); 
    return 0; 
}
 
