#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
	umask(0);
	if(mkfifo("mypipe",0644) < 0)
	{
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}
	int rfd = open("mypipe",O_RDONLY);
	if(rfd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);

	}
	char buf[1024];
	while(1)
	{
		buf[0]=0;
		printf("Please wait...\n");
		ssize_t s = read(rfd,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s-1] = 0;
			printf("process2 say# %s\n",buf);
		}
		else if(s == 0)
		{
			printf("process2 quit,exit now.\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

	}
	close(rfd);
	return 0;
}

