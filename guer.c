/*************************************************************************
	> File Name: guer.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 18 Mar 2018 01:57:38 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
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
		printf("child | %d\n",getpid());
		sleep(8);
	}
	else
	{
		printf("father | %d\n",getpid());
		sleep(3);
		exit(0);
	}
	return 0;
}
