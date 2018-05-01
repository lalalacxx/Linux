#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void *rout(void *arg)
{
    (void)arg;
    for(;;)
    {
        printf("I am thread 1\n");
        sleep(1);
    }
}




int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,rout,NULL);
    if(ret != 0)
    {
        fprintf(stderr,"pthread_create:%s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }
    for(;;)
    {
        printf("I am main thread\n");
        sleep(1);
    }
    
    return 0;
}
