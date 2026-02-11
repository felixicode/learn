#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

__thread int tls_counter = 0;

void *thread_fn1(void *arg)
{
	while (1){
		tls_counter++;
		printf("tid:%ld tls_counter:%d\n", syscall(SYS_gettid), tls_counter);
		sleep(1);
	}
	return NULL;
}

void *thread_fn2(void *arg)
{
	while (1) {
		tls_counter--;
		printf("tid:%ld tls_counter:%d\n", syscall(SYS_gettid), tls_counter);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t p1, p2;

	pthread_create(&p1, NULL, thread_fn1, NULL);
	pthread_create(&p2, NULL, thread_fn2, NULL);

	while(1)
		sleep(1);
}
