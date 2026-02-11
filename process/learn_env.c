#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void print_env(const char *c)
{
	printf("%s:%s\n", c, getenv(c));
}

int main()
{
	char c[128];

	scanf("%s", c);

	print_env(c);

	return 0;
}
