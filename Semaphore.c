#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t  smp;
int counter = 0;

void* start_function(void* value)
{
    printf("%s is now entering the thread function.\n", (char*)value);
    sem_wait(&smp);
    counter++;
    sleep(2);
    sem_post(&smp);
    printf("%s is now leaving the thread function.\n", (char*)value);
    printf("Value of counter is: %d\n", counter);
    pthread_exit(value);
}

main()
{
    int res;
    pthread_t thread1, thread2;

    sem_init(&smp, 0, 1);

    res = pthread_create(&thread1, NULL, start_function, "Thread1");
    if (res != 0)
	{
        perror("Creation of thread failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread2, NULL, start_function, "Thread2");
    if (res != 0)
	{
        perror("Creation of thread failed");
        exit(EXIT_FAILURE);
    }
 
    res = pthread_join(thread1, NULL);
    if (res != 0)
	{
        perror("Joining of thread failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread2, NULL);
    if (res != 0)
	{
        perror("Joining of thread failed");
        exit(EXIT_FAILURE);
    }

    sem_destroy(&smp);
}