#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<sys/types.h>
#include<pthread.h>

long long g_num;
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

#if 0
void *test(void *arg)
{
	while(1)
	{
		int i;
		long long a = g_num, b;
		for(i = 0; i < 1000000; i++)
			g_num++;
		b = g_num;
		fprintf(stderr, "tid:%ld a:%8lld b:%8lld %lld\n", syscall(SYS_gettid), a, b, (b - a));
	}

	return NULL;
}
#endif

void *test_lock(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&g_lock);
		int i;
		long long a = g_num, b;
		for(i = 0; i < 1000000; i++)
			g_num++;
		b = g_num;
		pthread_mutex_unlock(&g_lock);
		printf("tid:%ld a:%8lld b:%8lld %lld\n", syscall(SYS_gettid), a, b, (b - a));
	}

	return NULL;
}

int main()
{
	int r, i;
	pthread_t p;
	for(i = 0; i < 10; i++)
		r = pthread_create(&p, NULL, test_lock, NULL);
	sleep(60);

	return 0;
}
