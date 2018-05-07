#pragma once


#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<string.h>

#define PATHNAME "."
#define PROJ_ID 0X4444

#define p1_type 1
#define p2_type 2

struct msgbuf
{
	long mtype;
	char mtext[1024];
};

int createMsgQueue();
int getMsgQueue();
int destroyQueue(int msgid);
int sendMsg(int msgid,int who,char *msg);
int recvMsg(int msgid,int recvType,char out[]);
