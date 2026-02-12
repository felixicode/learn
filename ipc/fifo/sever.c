#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "common.h"

int main()
{
	char buf[1024];
	int fd_read, fd_write;

	mkfifo(FIFO1, 0666);
	mkfifo(FIFO2, 0666);

	fd_read = open(FIFO1, O_RDONLY);
	fd_write = open(FIFO2, O_WRONLY);

	while(1)
	{
		read(fd_read, buf, sizeof(buf));
		printf("Server received: %s\n", buf);

		if(!strcmp(buf, "bye,bye"))
		{
			write(fd_write, buf, strlen(buf));
			break;
		}
		else
			write(fd_write, buf, strlen(buf));
	}

	close(fd_read);
	close(fd_write);

	return 0;
}
