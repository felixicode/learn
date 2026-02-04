#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_fn(void *arg)
{
	int i;

	printf("1\n");

	for (i = 0; i <= 10 ;i++)
	{
		sleep(1);
		printf("1\n");
	}

	return NULL;
}

int main()
{
	int r;
	pthread_t p;

	r = pthread_create(&p, NULL, thread_fn, NULL);
	r = pthread_join(p, NULL);
}
