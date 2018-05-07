#include<stdio.h>

int main()
{
	int i = 0;
	char buf[102] = "#";
	char sym[] = "|/-\\";
	for(i = 1;i <= 100;i++)
	{
		buf[i] = '#';
		//设置进度条为蓝色，百分比进度为绿色
        //r为不换行，光标移动到行首输出
        printf("\033[34m[%-100s]\033[32m[%d%]\033[0m[%c]\r",buf,i,sym[i%4]);
        //因为没有遇到n，因此需要刷新缓冲区使之立刻输出printf的内容
        //否则会先执行usleep
		fflush(stdout);
        //Linux下usleep是按毫秒计算的
		usleep(80000);
	
	}
	printf("\n");
	return 0;
}
