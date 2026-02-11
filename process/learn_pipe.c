#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	int pipe_fd[2];
	char buf[128];
	char msg[] = "Hello, pipe!";
	pid_t pid;

	if (pipe(pipe_fd) == -1) {
		perror("pipe");
		return 1;
	}

	pid = fork();

	if (pid == 0) {
		close(pipe_fd[1]);
		read(pipe_fd[0], buf, sizeof(buf));
		printf("Child received: %s\n", buf);
		close(pipe_fd[0]);
	} else {
		close(pipe_fd[0]);
		write(pipe_fd[1], &msg, sizeof(msg));
		close(pipe_fd[1]);
		wait(NULL);
	}

	return 0;
}
