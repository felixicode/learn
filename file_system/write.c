#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
	char c[256];
	int fd = open("abc", O_RDWR | O_CREAT | O_TRUNC, 07777);
	fgets(c, sizeof(c), stdin);
	ssize_t r = write(fd, c , strlen(c) - 1);
	return 0;
}
