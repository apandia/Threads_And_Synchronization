#include <stdio.h>
#include <pthread.h>

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t ml = PTHREAD_MUTEX_INITIALIZER;
 
int counter = 1;

//Program to print 1,2,1,2,1,2.... in sequence
//ThreadFunction1 and threadFunction2 will be called in sequence. Synchronization is done using condition varaiable.
 
void* threadFunc1()
{
    while (1)
    {
        pthread_mutex_lock(&ml);
        
        if (counter == 1)
        {
            printf("1\n");
            
            counter = 2;
            
            //signal to thread2 and then wait on thread1
            pthread_cond_signal(&cv);
            
            pthread_cond_wait(&cv, &ml);
        }
        
        pthread_mutex_unlock(&ml);
    }
 
    return NULL;
}

void* threadFunc2()
{
    while (1)
    {
        pthread_mutex_lock(&ml);
        
        if (counter == 2)
        {
            printf("2\n");
            
            counter = 1;

            //signal to thread1 and then wait on thread2
            pthread_cond_signal(&cv);
            
            pthread_cond_wait(&cv, &ml);
        }
        
        pthread_mutex_unlock(&ml);
    }
 
    return NULL;
}
 
int main()
{
    pthread_t tid1, tid2;
 
    pthread_create(&tid1, NULL, threadFunc1, NULL);
    
    sleep(1);
 
    pthread_create(&tid2, NULL, threadFunc2, NULL);
 
    pthread_join(tid2, NULL);
 
    return 0;
}