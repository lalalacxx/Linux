#include"com.h"

int main()
{
	int semid = createSemSet(1);
	initSem(semid,0,1);
	pid_t id = fork();
	if(id == 0)
	{
		//child
		int _semid = getSemSet(0);
		while(1)
		{
			P(_semid,0);
			printf("X");
			fflush(stdout);
			usleep(123456);
			printf("X ");
			fflush(stdout);
			usleep(123456);
			V(_semid,0);
		}
	}
	else
		{
			//father
			while(1)
			{
				P(semid,0);
	    		printf("Y");
	    		fflush(stdout);
	    		usleep(323456);
	    		printf("Y ");
	    		fflush(stdout);
	    		usleep(223456);
	    		V(semid,0);
			}
			wait(NULL);
		}
	destroySemSet(semid);
	return 0;
}
