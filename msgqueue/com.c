#include"com.h"
//success > 0 ,failed == -1
static int comMsgQueue(int flags)

{
	key_t key = ftok(PATHNAME,PROJ_ID);
	if(key < 0)
	{
		perror("ftok");
		return -1;
	}
	int msgid = msgget(key,flags);
	if(msgid < 0)
	{
		perror("msgget");
	}
	return msgid;
}
int createMsgQueue()
{
	return comMsgQueue(IPC_CREAT|IPC_EXCL|0666);
}
int getMsgQueue()
{
	return comMsgQueue(IPC_CREAT);
}
int destroyMsgQueue(int msgid)
{
	if(msgctl(msgid,IPC_RMID,NULL) < 0)
	{
		perror("msgctl");
		return -1;
	}
	return 0;
}
int sendMsg(int msgid,int who,char *msg)
{
	struct msgbuf buf;
	buf.mtype = who;
	strcpy(buf.mtext,msg);
	if(msgsnd(msgid,(void*)&buf,sizeof(buf.mtext),0) < 0)
	{
		perror("msgsnd");
		return -1;
	}
	return 0;
}
int recvMsg(int msgid,int recvType,char out[])
{
	struct msgbuf buf;
	if(msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),recvType,0) < 0)
	{
		perror("msgrcv");
		return -1;
	}
	strcpy(out,buf.mtext);
	return 0;
}





