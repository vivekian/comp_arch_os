#include <cstdio>
#include <thread> 
#include <iostream> 
#include <semaphore.h> 

using namespace std; 

namespace { 
    const int MAX = 10; 
    int buffer[MAX]; 
    int place = 0; 
    int use = 0; 
}

void put(int value) 
{ 
    buffer[place] = value; 
    place = (place + 1) % MAX; 
} 

int get() 
{ 
    int tmp = buffer[use]; 
    use = (use + 1) % MAX;
    return tmp; 
}

sem_t *s_empty; 
sem_t *s_full;
sem_t *s_mutex; 

void producer() 
{ 
    for (int i=0; i<10; ++i) { 
        sem_wait(s_empty);
        sem_wait(s_mutex);
        put(i);
        sem_post(s_mutex);
        sem_post(s_full);
    }
} 

void consumer()
{ 
    for (int i=0; i<10 ;++i) { 
        sem_wait(s_full);
        sem_wait(s_mutex);
        int tmp = get();
        sem_post(s_mutex);
        sem_post(s_empty);
        cout << tmp << endl; 
    }
} 

int main() 
{ 
    s_empty = sem_open("s_empty", O_CREAT, 0, MAX);
    s_full = sem_open("s_full", O_CREAT, 0, 0);
    s_mutex = sem_open("s_mutex", O_CREAT, 0, 1);

    thread t2(consumer);
    thread t1(producer); 
    
    t1.join();
    t2.join();

    sem_close(s_empty);
    sem_close(s_full);
    sem_close(s_mutex); 
}
