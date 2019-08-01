#include "inc.h" 

int main(int argc,char*argv[])
{
	if(argc != 3)
	{
		printf("cmd is error,the correct is : %s a.txt,b.txb\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	char *infile = argv[1];
	printf("infile=%s\n",infile);
	char *outfile = argv[2];
	printf("outfile=%s\n",outfile);
	
	int infd = open(infile,O_RDONLY,0);
	if(-1 == infd)
	{
		printf("open %s fail\n",argv[1]);
		printf("%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	int filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int outfd = open(outfile,O_WRONLY|O_CREAT,filePerms);
	if(-1 == outfd)
	{
		printf("open %s fail\n",argv[2]);
		printf("%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	int buf[1024] = {'\0'};
	int readnum;
	while((readnum = read(infd,buf,1024)) > 0)
	{
		write(outfd,buf,readnum);
		memset(buf,'\0',sizeof(buf));
	}
	if(-1 == close(infd))
	{
		exit(EXIT_FAILURE);
	}
	if(-1 == close(outfd))
	{
		exit(EXIT_FAILURE);
	}
	return 0;
}
