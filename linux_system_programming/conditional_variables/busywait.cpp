#include <stdio.h> 
#include <pthread.h> 

unsigned long long x = 0; 
const unsigned long long y = 10000000000; 

void* a(void* arg) 
{ 
    while (x < y); 
    printf("now x = y\n"); 
} 

void *b(void* arg) 
{ 
    while (x != y)  
        x++;
} 

int main() 
{ 
    pthread_t tida, tidb; 
     
    if (pthread_create(&tida, NULL, a, NULL)) 
    { 
        printf("thread creation failed\n"); 
        return 1;  
    } 

    if (pthread_create(&tidb, NULL, b, NULL)) 
    { 
        printf("thread creation failed\n"); 
        return 1; 
    } 

    pthread_join(tida, NULL); 
    pthread_join(tidb, NULL); 

    return 0; 
} 
