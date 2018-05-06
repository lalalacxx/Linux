#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

int ticket = 100;
pthread_mutex_t mutex;

void *route(void *arg)
{
    char *id = (char*)arg;
    while(1)
    {
        //加锁
        pthread_mutex_lock(&mutex);
        if(ticket > 0)
        {
            usleep(1000);
            printf("%s sells ticket:%d\n",id,ticket);
            ticket--;
            //解锁
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            //解锁
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    return NULL;
}

int main()
{
    pthread_t t1,t2,t3;

    //初始化互斥量
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&t1,NULL,route,"thread 1");
    pthread_create(&t2,NULL,route,"thread 2");
    pthread_create(&t3,NULL,route,"thread 3");

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    //销毁互斥量
    pthread_mutex_destroy(&mutex);
}
