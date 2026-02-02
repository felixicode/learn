#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

void format_size(long n, char *size)
{
	long long k = n / 1024;
       	long long m = k / 1024;
        long long g = m / 1024;
	if(g)
	{
		double d = (double)n / (1024.0 * 1024 * 1024);
		sprintf(size, "%6.2lf GiB", d);
	}
	else if(m)
	{
 		double d = (double)n / (1024.0 * 1024);
                sprintf(size, "%6.2lf MiB", d);
	}
	else if(k)
	{
	 	double d = (double)n / 1024.0;
                sprintf(size, "%6.2lf KiB", d);
	}
	else
	{
		double d = (double)n;
                sprintf(size, "%6.2lf B", d);
	}		
}

int main(int argc, char **argv)
{
	char buf[4096], *path;
	struct stat st;
	if(argc == 1)
		path = ".";
	else
		path = argv[1];
	DIR *dp = opendir(path);
	if(dp == NULL)
	{
		printf("failed to opern %s\n", path);
		return 0;
	}	
	
	while(1)
	{
		struct dirent *r = readdir(dp);
		if(r == NULL)
			break;
		sprintf(buf, "%s/%s", path,r->d_name);
		printf("%-30s ", r->d_name);
		int l = stat(buf, &st);
		if(l)
		{
			printf("%s\n", strerror(errno));
			continue;	
		}
		char size[1024];
		format_size(st.st_size, size);
		printf("%s\n", size);
	}
	closedir(dp);
	return 0;
}
