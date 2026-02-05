#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main()
{
        while(1)
        {
                pid_t pid = fork();
                printf("%d\n", getpid());
        }
}
