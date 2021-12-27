#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

bool thread_finished = 0;

void* start_function(void* value)
{
    printf("%s is now entering the thread function.\n", (char*)value);
    sleep(4);
    thread_finished =1;
    printf("%s is now leaving the thread function.\n", (char*)value);
    pthread_exit(value);  
}

main()
{
    int res,err;
    pthread_attr_t attr;
    pthread_t thread1;

    res = pthread_attr_init(&attr);
    if (res != 0)
	{
        perror("Attribute init failed");
        exit(EXIT_FAILURE);
    }
	
    res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (res != 0)
	{
        perror("Setting detached state failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread1, &attr, start_function, (void*)"Thread1");
    if (res != 0)
	{
        perror("Creation of thread failed");
        exit(EXIT_FAILURE);
    }

    while(!thread_finished)
	{
        printf("Waiting for thread1 to finish.\n");
        sleep(1);
    }

    printf("Child thread finished.\n");    
    pthread_attr_destroy(&attr);
}