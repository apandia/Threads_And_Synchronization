#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <pthread.h>

pid_t gettid()
{
    pid_t tid = syscall (SYS_gettid);
}

void* start_function(void* value)
{
    pid_t tid = gettid();
    printf("Thread start function is running for: %u\n", (unsigned int)pthread_self());
    printf("The TID of thread is: %ld\n", (long int)tid);
    printf("PID of parent process is: %d\n", getpid());
    sleep(5);
    pthread_exit(value);
}

main()
{
    int res;
    pthread_t thread1, thread2;
    void* threadReturnValue;

    printf("PID of main process: %d\n", getpid());

    res = pthread_create(&thread1, NULL, start_function, "thread-one");
    if (res != 0)
	{
        perror("Creation of thread failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread1 created with id: %u\n", (unsigned int)thread1);

    res = pthread_create(&thread2, NULL, start_function, "thread-two");
    if (res != 0) 
	{
        perror("Creation of thread failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread2 created with id: %u\n", (unsigned int)thread2);
 
    res = pthread_join(thread1, &threadReturnValue);
    if (res != 0)
	{
        perror("Joining of thread failed");
        exit(EXIT_FAILURE);
    }
    printf("%s joined.\n", (char*)threadReturnValue);

    res = pthread_join(thread2, &threadReturnValue);
    if (res != 0)
	{
        perror("Joining of thread failed");
        exit(EXIT_FAILURE);
    }	
    printf("%s joined.\n", (char*)threadReturnValue);
}