#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage:%s [ip] [port]\n",argv[0]);
        return 3;
    }
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        perror("socket");
        return 3;
    }
    //客户端不需要绑定
    

    char buf[128];
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons( atoi(argv[2]) );
    server.sin_addr.s_addr = inet_addr( argv[1] );
    socklen_t len = sizeof(server);
    for(;;)
    {
        buf[0] = 0;
        ssize_t s = read(0,buf,sizeof(buf)-1);
        if(s > 0)
        {
            buf[s-1] = 0;//-1是为了不把回车读进来
            sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&server,len);
            s = recvfrom(sock,buf,sizeof(buf)-1,0,NULL,NULL);//知道是谁给我发的，所以设为空
            if(s > 0)
            {
                buf[s] = 0;
                printf("server echo# %s\n",buf);
            }
        }
    }
    close(sock);
    return 0;
}









