/* gcc pthreadscope.c –o pthreadscope -lpthread */
#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *runner(void *param);

int main(int argc, char* argv[])
{
        int i, scope;
        pthread_t tid[NUM_THREADS];
        pthread_attr_t attr;

        /* get the default attributes */
        pthread_attr_init(&attr);

	puts("Initial scope:");
        /* first inquire on the current scope */
        if(pthread_attr_getscope(&attr, &scope) != 0)
                fprintf(stderr, "Unable to get scheduling scope\n");
        else
        {
                if(scope == PTHREAD_SCOPE_PROCESS)
                        printf("PTHREAD_SCOPE_PROCESS\n");
                else if(scope == PTHREAD_SCOPE_SYSTEM)
                        printf("PTHREAD_SCOPE_SYSTEM\n");
                else
                        fprintf(stderr, "Illegal scope value.\n");
        }

	puts("Set new scope.");
	 /* set the scheduling algorithm to PCS or SCS */
        
	/* Linux doens not support PTHREAD_SCOPE_PROCESS :( */
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
        // pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

	puts("New scope:");
        if(pthread_attr_getscope(&attr, &scope) != 0)
                fprintf(stderr, "Unable to get scheduling scope\n");
        else
        {
                if(scope == PTHREAD_SCOPE_PROCESS)
                        printf("PTHREAD_SCOPE_PROCESS\n");
                else if(scope == PTHREAD_SCOPE_SYSTEM)
                        printf("PTHREAD_SCOPE_SYSTEM\n");
                else
                        fprintf(stderr, "Illegal scope value.\n");
        }

        /* create the threads */
        for(i = 0; i < NUM_THREADS; i++)
                pthread_create(tid + i, &attr, runner, &i);

        /* now join on each thread */
        for(i = 0; i < NUM_THREADS; i++)
                pthread_join(tid[i], NULL);
}

/* Each thread will begin control in this function */
void *runner(void *param)
{
        /* do some work ... */
        printf("I am the thread \n");
        pthread_exit(0);
}
