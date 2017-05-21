#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 100
#define NUM_ITER   50000000

void * thread_inc(void *arg);
void * thread_des(void *arg);

long long num = 0;

int main(int argc, char* argv[])
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	printf("size: %d\n", sizeof(long long));
	
	for(i=0; i<NUM_THREAD; i++)
	{
		if(i%2)
		{
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		}
		else
		{
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
		}
	}

	for(i=0; i<NUM_THREAD; i++)
		pthread_join(thread_id[0], NULL);

	printf("result: %d\n", num);
	return 0;
}

void * thread_inc(void *arg)
{
	int i;
	for(i=0; i<NUM_ITER; i++)
		num+=1;
	return NULL;
}

void * thread_des(void *arg)
{
	int i;
	for(i=0; i<NUM_ITER; i++)
		num-=1;
	return NULL;
}
