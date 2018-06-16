#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAX 128

int startUp(char *ip,int port)
{
    //创建监听套接字文件描述符
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }
    //填充
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);
    //绑定
    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
    {
        perror("bind");
        exit(3);
    }
    //监听
    if(listen(sock,5) < 0)
    {
        perror("listen");
        exit(4);
    }
    return sock;
}
void service(int sock,char *ip,int port)
{
    char buf[MAX];
    while(1)
    {
        ssize_t s = read(sock,buf,sizeof(buf)-1);
        if(s > 0)
        {
            buf[s] = 0;
            printf("[%s:%d] say: %s\n",ip,port,buf);
            write(sock,buf,strlen(buf));
        }
        else if(s == 0)
        {
            printf("client [%s:%d] quit \n",ip,port);
            break;
        }
        else
        {
            perror("read");
            break;
        }
    }
}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("usage:%s [ip] [port]\n",argv[0]);
        return 1;
    }
    int listen_sock = startUp(argv[1],atoi(argv[2]));
    struct sockaddr_in peer;
    char ipBuf[24];
    for(;;)
    {
        ipBuf[0] = 0;
        socklen_t len = sizeof(peer);
        int new_sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
        if(new_sock < 0)
        {
            //连接失败
            perror("accept");
            //继续下一个连接
            continue;
        }
        //连接成功
        
        //转换ip,将4字节IP地址转换为点分十进制IP地址
        inet_ntop(AF_INET,(const void *)&peer.sin_addr,ipBuf,sizeof(ipBuf));
        //将网络端口号转换为主机端口号
        int p = ntohs(peer.sin_port);
        //打印获得哪个连接
        printf("get a connect,[%s:%d]\n",ipBuf,p);

        pid_t id = fork();
        if(id == 0 )
        {
            //child
            close(listen_sock);
            //循环的创建子进程但子进程后续会退出
            //子进程调用fork
            if(fork() > 0)
            {
                exit(0);
            }
            //子进程创建的子进程(孙子进程)往后走
            //子进程退出以后，孙子进程变成了孤儿进程
            //爷孙关系没有等待与被等待的需求
            //孤儿进程会被1号进程领养，那么孤儿进程的父进程就是1号进程
            //所以孤儿进程的回收就不用父进程负责，而是由1号进程负责
            service(new_sock,ipBuf,p);
            close(new_sock);
            exit(0);
        }
        else if(id > 0)
        {
            //father(父进程不会退出，而子进程会退出，由于循环
            //所以就有大量的子进程退出，就会产生大量的僵尸进程)
            //不关心退出码，以阻塞方式等
            close(new_sock);
            waitpid(id,NULL,0);
        }
        else
        {
            perror("fork");
            continue;
        }
    }
    return 0;
}
