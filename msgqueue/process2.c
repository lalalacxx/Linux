#include"com.h"
int main()
{
	int msgid = getMsgQueue();
	char buf[1024];
	while(1)
	{
		buf[0] = 0;
		printf("Please Enter# ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf));
		if(s > 0)
		{
			buf[s-1] = 0;
			sendMsg(msgid,p2_type,buf);
			printf("send done,wait recv...\n");
		}
		recvMsg(msgid,p1_type,buf);
		printf("process1 say: %s\n",buf);
	}
	return 0;
}
