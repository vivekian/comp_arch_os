#include <stdio.h> 
#include <pthread.h> 

unsigned long long x = 0; 
const unsigned long long y = 1000000000;  

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t v = PTHREAD_COND_INITIALIZER;  

void* cmp(void* arg) 
{
    pthread_mutex_lock(&mutex);  
    
    while (x < y) {
        pthread_cond_wait(&v, &mutex);
    }; 
   
    pthread_mutex_unlock(&mutex);  
    printf("now x = y\n"); 
} 

void *inc(void* arg) 
{
    while (x != y) {
        pthread_mutex_lock(&mutex);  
        x++;
        pthread_mutex_unlock(&mutex); 
    } 

    pthread_cond_signal(&v); 
} 

int main() 
{ 
    pthread_t tida, tidb; 
     
    if (pthread_create(&tida, NULL, cmp, NULL)) 
    { 
        printf("thread creation failed\n"); 
        return 1;  
    } 

    if (pthread_create(&tidb, NULL, inc, NULL)) 
    { 
        printf("thread creation failed\n"); 
        return 1; 
    } 

    pthread_join(tida, NULL); 
    pthread_join(tidb, NULL); 

    return 0; 
} 
