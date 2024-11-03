#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main()
{
	struct timeval current_time;
	struct tm *ti;
	char time_str[64] = { 0 };

	for(;;)
	{
		usleep(1000000);
		memset(time_str, 0, sizeof(time_str));
		gettimeofday(&current_time, NULL);

		ti = localtime(&current_time.tv_sec);
		strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", ti);

		sprintf(time_str + strlen(time_str), ".%06ld", current_time.tv_usec);

		printf("%s\n", time_str);
	}
	return 0;
}
