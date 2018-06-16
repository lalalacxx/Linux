#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAX 128

//   ./client 127.0.0.1 8080
int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("usage:%s [ip] [port]\n",argv[0]);
        return 1;
    }
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        return 2;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    //客户端向服务器发起连接，对应于服务器的listen和accept
    //经过listen之后才允许发起连接，
    //connect之后才有可能通过accept获得这个新连接
    //成功返回0，失败返回-1
    if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0)
    {
        perror("connect");
        return 3;
    }
    //一旦连接成功，客户就可以通过刚刚创建的sock套接字
    //与服务器端的new_sock进行通信
    char buf[MAX];
    while(1)
    {
        //服务器端先读后写，客户端先写后读
        printf("please say: ");
        fflush(stdout);
        //从标准输入里读到buf中去
        ssize_t s = read(0,buf,sizeof(buf)-1);
        if(s > 0)
        {
            buf[s-1] = 0; //不要后面键入的回车
            if(strcmp("quit",buf) == 0)
            {
                printf("client quit\n");
                break;
            }
            //向服务器发送读到的内容
            write(sock,buf,strlen(buf));
            //接收服务器回传的消息
            s = read(sock,buf,sizeof(buf)-1);
            buf[s] = 0;
            printf("Server Echo: %s\n",buf);
        }
    }
    close(sock);
    return 0;
}
