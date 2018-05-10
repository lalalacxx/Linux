#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include<dirent.h>

void copy_file(const char *src,const char *dst,mode_t mode)
{	
	FILE *fp_dst = fopen(dst,"w");
	FILE *fp_src = fopen(src,"r");
	if(fp_dst == NULL || fp_src == NULL)
	{
		fprintf(stderr,"open file error\n");
		return ;
	}
	chmod(dst,mode);

	char buf[10] = {};
	int r;
	while((r = fread(buf,1,sizeof(buf),fp_src)) > 0)
	{
		fwrite(buf,1,r,fp_dst);
	}

	fclose(fp_dst);
	fclose(fp_src);
}

void copy_dir(const char *src,const char *dst)
{
	DIR *pdir = opendir(src);
	struct dirent *pd = NULL;
	while((pd = readdir(pdir)) != NULL)
	{
		if(strcmp(pd->d_name,".") == 0 || strcmp(pd->d_name,"..") == 0 )
			continue;
		int len = strlen(src)+2+strlen(pd->d_name);
		char *src_name = (char *)malloc(len);
		memset(src_name,0x00,len);
		sprintf(src_name,"%s/%s",dst,pd->d_name);

		len = strlen(dst)+2+strlen(pd->d_name);
		char *dst_name = (char *)malloc(len);
		memset(dst_name,0x00,len);
		sprintf(dst_name,"%s/%s",dst,pd->d_name);
		
		struct stat sbuf_src;	
		lstat(src_name,&sbuf_src);
		if(S_ISREG(sbuf_src.st_mode))
		{
			copy_file(src_name,dst_name,sbuf_src.st_mode);
		}
		else if(S_ISDIR(sbuf_src.st_mode))
		{
			mkdir(dst_name,sbuf_src.st_mode);
			copy_dir(src_name,dst_name);
		}
	}
}

int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr,"%s src dst\n",argv[0]);
		exit(1);
	}

	struct stat sbuf_src;
	if(lstat(argv[1],&sbuf_src) == -1)
	{
		fprintf(stderr,"%s not exist\n",argv[1]);
		exit(1);
	}
	mode_t old = umask(0);
	if(S_ISREG(sbuf_src.st_mode))
	{
		struct stat sbuf_dst;
		if(lstat(argv[2],&sbuf_dst) == -1)
		{
			copy_file(argv[1],argv[2],sbuf_src.st_mode);
		}
		else if(S_ISREG(sbuf_dst.st_mode))
		{
			printf("target file is already exist, ?[y/n] ");
			char c = 'n';
			scanf("%[yYnN]",&c);
			if(c == 'y' || c == 'Y')
			{
				copy_file(argv[1],argv[2],sbuf_src.st_mode);
			}
		}
	}
	else if(S_ISDIR(sbuf_src.st_mode))
	{
		int len = strlen(argv[1])+2+strlen(argv[1]);
		char *tmp = (char*)malloc(len);
		memset(tmp,0x00,len);
		sprintf(tmp,"%s/%s",argv[2],argv[1]);
		copy_file(argv[1],tmp,sbuf_src.st_mode);
	}
	else if(S_ISDIR(sbuf_src.st_mode))
	{
		struct stat sbuf_dst;
		if(lstat(argv[2],&sbuf_src.st_mode))
		{
			mkdir(argv[2],sbuf_src.st_mode);
			copy_dir(argv[1],argv[2]);
		}
		else if(S_ISREG(sbuf_dst.st_mode))
		{
			fprintf(stderr,"copy directory to file is disabled\n");
			exit(1);
		}
		else if(S_ISDIR(sbuf_dst.st_mode))
		{
			int len = strlen(argv[1])+2+strlen(argv[1]);
			char *tmp = (char*)malloc(len);
			memset(tmp,0x00,len);
			sprintf(tmp,"%s/%s",argv[2],argv[1]);
			copy_dir(argv[1],tmp);
		}
	}
	umask(old);
}
