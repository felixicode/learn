#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

char g_buf[2 * 1024 * 1024];
int g_posw;
int g_drop;
bool g_need_flush = false;

pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  g_cond;

void *thread_fn(void *arg)
{
	struct tm *ti;
	char time_str[64] = { 0 };
	struct timeval tv;
	int id = syscall(SYS_gettid);
	char usec_str[10];

	while (1) {
		memset(time_str, 0, sizeof(time_str));

		gettimeofday(&tv, NULL);
		ti = localtime(&tv.tv_sec);
		strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", ti);

		snprintf(usec_str, sizeof(usec_str), ".%07ld", tv.tv_usec);
		if (strlen(time_str) + strlen(usec_str) < sizeof(time_str))
			strcat(time_str, usec_str);

		pthread_mutex_lock(&g_lock);
		if (g_posw >= (sizeof(g_buf) / 2)) {
			g_need_flush = true;
			pthread_cond_signal(&g_cond);
			if(g_posw >= sizeof(g_buf))
				g_drop++;
		} else {
			g_posw += snprintf(g_buf + g_posw, sizeof(g_buf) - g_posw, "%s tid:%d num:%ld\n",time_str, id, random());
		}

		pthread_mutex_unlock(&g_lock);
		usleep(1 * 900 * 998);
	}

	return NULL;
}

void *thread_log_fn(void *arg)
{
	char *buf = malloc(8 * 1024 * 1024);
	int fd = open("log.log", O_RDWR | O_CREAT | O_TRUNC, 06666);
	int n, r = 0;

	memset(buf, 0, 8 * 1024 * 1024);

	while (1) {
		pthread_mutex_lock(&g_lock);
		struct timespec tim;
		clock_gettime(CLOCK_REALTIME, &tim);
		tim.tv_sec += 5;
		while (!g_need_flush) {
			r = pthread_cond_timedwait(&g_cond, &g_lock, &tim);
			if(r == ETIMEDOUT)
				break;
		}

		if(r != ETIMEDOUT)
			g_need_flush = false;

		printf("wakeup by %s\n", r == ETIMEDOUT ? "timeout" : "data size");
		pthread_mutex_unlock(&g_lock);

		pthread_mutex_lock(&g_lock);
		memcpy(buf, g_buf, g_posw);
		n = g_posw;
		g_posw = 0;
		pthread_mutex_unlock(&g_lock);
		/* To avoid hold lock too long time, move 'write' out of the lock */
		write(fd, buf, n);
	}

	return NULL;
}

int main()
{
	int i, r;
	pthread_t p;

	srandom(time(NULL));

	for (i = 0; i < 10; i++)
		r = pthread_create(&p, NULL, thread_fn, NULL);

	r = pthread_create(&p, NULL, thread_log_fn, NULL);

	while (1) {
		sleep(1);
		printf("drop:%d\n", g_drop);
		pthread_mutex_lock(&g_lock);
		g_drop = 0;
		pthread_mutex_unlock(&g_lock);
	}
}
