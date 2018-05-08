#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	//printf("before:pid->%d\n",getpid());

	//pid_t id = fork();
	//if(id < 0)
	//{
	//	perror("fork");
	//	return;
	//}
//	else if(id == 0)
	//{
	//	printf("child\n");
	//}
	//else
	//{
	//	printf("father\n");
	//	return;
	//}
//	printf("after:pid->%d,fork return %d\n",getpid(),id);
	//sleep(1);
	int num = 20;
	pid_t id = vfork();
	if(id < 0)
	{
		perror("vfork");
		return;
	}
	else if(id == 0)
	{
		sleep(1);
		num = 2000;
		printf("child num:%d\n",num);
		exit(0);
	}
	else
	{
		printf("father num:%d\n",num);
	}
	return 0;
}
