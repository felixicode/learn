#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

void *test(void *arg) {
	int i;

	printf("Thread: start\n");
	for (i = 0; i < 10; i++) {
		printf("Thread: Hello from thread\n");
		sleep(1);
	}
	printf("Thread: finished\n");

	return NULL;
}

int main() {
	int i, ret;
	pthread_t p;

	printf("start create thread\n");
	ret = pthread_create(&p, NULL, test, NULL);
	
	
	printf("Main: start\n");
	for (i = 0; i < 5; i++) {
		printf("Main: Hello from thread\n");
		sleep(1);
	}
	printf("Main: finished\n");

	printf("Main: start wait child thread\n");
        pthread_join(p, NULL);
	printf("Main: finished to wait child thread\n");

	printf("All threads have completed\n");

	return 0;
}
