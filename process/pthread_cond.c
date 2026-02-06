#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

int g_arr[16];
int g_nr;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_cond = PTHREAD_COND_INITIALIZER;

void *thread_fn1(void *arg)
{
	int i;
	srandom(time(NULL));
	while (1)
	{
		usleep(100000);
		pthread_mutex_lock(&g_mutex);
		i++;
		i %= 10;
		g_arr[i] = (int)random();
		pthread_mutex_unlock(&g_mutex);
		if(!i)
		{
			g_nr = 1;
			pthread_cond_signal(&g_cond);
		}
	}
}

void *thread_fn2(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&g_mutex);
		while(!g_nr)
			pthread_cond_wait(&g_cond, &g_mutex);
		g_nr = 0;
		int i, acc;
		for(i = 0; i < 10; i++)
			acc += g_arr[i];
		printf("receive a sigal, the sum is: %d\n", acc);
		pthread_mutex_unlock(&g_mutex);
	}
}

int main()
{
	int r;
	pthread_t p1, p2;

	r = pthread_create(&p1, NULL, thread_fn1, NULL);
	r = pthread_create(&p1, NULL, thread_fn2, NULL);

	while (1)
		sleep(1);
}
