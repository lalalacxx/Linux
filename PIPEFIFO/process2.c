#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

int main()
{
	int wfd = open("mypipe",O_WRONLY);
	if(wfd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);				
	}
	char buf[1024];
	while(1)
	{
		buf[0]=0;
		printf("Please enter#\n");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			write(wfd,buf,strlen(buf));
		}
		else if(s <= 0)
		{
			perror("read");
			exit(EXIT_FAILURE);				
		}											
	}
	close(wfd);
	return 0;
}
