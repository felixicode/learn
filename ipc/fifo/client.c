#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "common.h"

int main()
{
	char buf[1024] = {0};
	int fd_read, fd_write;

	fd_write = open(FIFO1, O_WRONLY);
	fd_read = open(FIFO2, O_RDONLY);

	while (1) {
		printf("client:");
		scanf("%s", buf);
		write(fd_write, buf, sizeof(buf));

		memset(buf, 0, sizeof(buf));
		read(fd_read, buf, sizeof(buf));
		if (!strcmp(buf, "bye,bye"))
			break;
		printf("Client received: %s\n", buf);
	}

	close(fd_write);
	close(fd_read);

	return 0;
}
