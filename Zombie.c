#include<stdio.h>
#include<stdlib.h>
int main()
{
	pid_t id = fork();
	if(id < 0)
	{
		perror("fork");
		return 1;
	}
	else if(id == 0)
	{
		printf("child | %d is begin Z...\n",getpid());
		sleep(2);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("father | %d is sleeping...\n",getpid());
		sleep(5);
	}
	return 0;
}
