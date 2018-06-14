#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

void service(int sock)
{
    char buf[128];
    for(;;)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        buf[0] = 0;//将字符串清空成为空串，则将第一个设置为\0即可
        ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
        if(s > 0)
        {
            buf[s] = 0;//最后一个设置为\0
            //显示那个ip的那个端口说了什么
            printf("[%s:%d]# %s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
            
            
            sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,len);
        }
    }
}
int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("usage:%s [ip] [port]\n",argv[0]);
        return 3;
    }
    //创建socket文件描述符
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        perror("socket");
        return 3;
    }
    //填充
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons( atoi(argv[2]) );
    local.sin_addr.s_addr = inet_addr( argv[1] );
    //绑定
    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
    {
        perror("bind");
        return 3;
    }
    //服务
    service(sock);
    close(sock);
    return 0;
}







