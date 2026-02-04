#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int main()
{
        int a;
        pid_t pid = fork();
        while(1)
        {
		if (!pid)
			pthread_setname_np(pthread_self(), "felix_c");
		else
			pthread_setname_np(pthread_self(), "felix_p");
        }
        return 0;
}
