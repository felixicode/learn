#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	time_t current_time;
	struct tm *ti;
	char time_str[64] = { 0 };

	for(;;)
	{
		sleep(1);
		memset(time_str, 0, sizeof(time_str));
		current_time = time(NULL);

		if (current_time == ((time_t)-1)) {
			fprintf(stderr, "failed to get time\n");
			return 1;
		}

		ti = localtime(&current_time);
		strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", ti);

		printf("%s\n", time_str);
	}
	return 0;
}
