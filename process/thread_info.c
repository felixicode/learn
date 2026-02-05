#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include<pthread.h>
//#include<sstring.h>

void *thread_fn(void *arg)
{
	char buf[128];
	pthread_getname_np(pthread_self(), buf, sizeof(buf));
	printf("pid:%d tid:%ld name:%s\n", getpid(), syscall(SYS_gettid), buf);
}

int main()
{
	int i, r;
	pthread_t p;

	for(i = 0; i < 10; i++)
		r = pthread_create(&p, NULL, thread_fn, NULL);
}
