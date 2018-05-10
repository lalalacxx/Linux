#include"com.h"

static int comSemSet(int nums,int flags)
{
	key_t key = ftok(PATHNAME,PROJ_ID);
	if(key < 0)
	{
		perror("ftok");
		return -1;
	}
	int semid = semget(key,nums,flags);
	if(semid < 0)
	{
		perror("semget");
		return -2;
	}
	return semid;
}
int createSemSet(int nums)
{
	return comSemSet(nums,IPC_CREAT|IPC-EXCL|0666);
}
int getSemSet(int nums)
{
	return comSemSet(nums,IPC_CREAT);
}
int initSem(int semid,int nums,int initval)
{
	union semun _un;
	_un.val = initval;
	if(semctl(semid,nums,SETVAL,_un) < 0)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}
static int comPV(int semid,int who,int op)
{
	struct sembuf _sf;
	_sf.sem_num = who;
	_sf.sem_op = op;
	_sf.sem_flg = 0;
	if(semop(semid,&_sf,1) < 0)
	{
		perror("semop");
		return -1;
	}
	return 0;
}
int P(int semid,int who)
{
	return comPV(semid,who,-1);
}
int V(int semid,int who)
{
	return comPV(semid,who,1);
}
int destroySemSet(int semid)
{
	if(semctl(semid,0,IPC_RMID) < 0)
	{
		perror("semctl");
		return -1;
	}
}
