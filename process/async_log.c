#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include<time.h>

void *thread_fn(void *arg)
{
	while(1)
	{
		int id = syscall(SYS_gettid);
		printf("tid:%d num:%ld\n", id, random());
		sleep(1);
	}
	return NULL;
}

int main()
{
	int i, r;
	pthread_t p;

	srandom(time(NULL));
	for(i = 0; i < 10; i++)
		r = pthread_create(&p, NULL, thread_fn, NULL);
	while (1)
		sleep(1);
}
