#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int n = 0, m = 0, i = 0;
	char c, num[256], buf[256];

	int fd = open("abc", O_RDWR | O_CREAT, 07777);
	ssize_t r = read(fd, &buf, 128);
	sscanf(buf,"%d %c %d", &n, &c, &m);

	if(c == '+') n += m;
	else if(c == '-') n -= m;
	else if(c == '*') n *= m;
	else if(c == '/') n /= m;
		
	sprintf(num,"%d", n);
	off_t l = lseek(fd, 0, SEEK_END);
	r = write(fd, num, strlen(num));
	return 0;
}

