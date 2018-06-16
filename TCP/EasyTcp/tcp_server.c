#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
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
        service(new_sock,ipBuf,p);
        close(new_sock);
    }
    return 0;
}












