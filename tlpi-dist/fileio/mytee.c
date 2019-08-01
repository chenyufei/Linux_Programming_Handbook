#include "inc.h"

#define BUF_SIZE (1024)

int main(int argc,char*argv[])
{
	if(argc != 2 && argc != 3)
	{
		printf("para is error\n");
		printf("correct para ex: ./mytee aa.txt or ./mytee -a aa.txt\n");
		exit(-1);
	}

	int openFlags = O_CREAT | O_WRONLY;
	char * outfile;
	int flags = 0;
	int opt;
	 while ((opt = getopt(argc, argv, "a:")) != -1) {
               switch (opt) {
               case 'a':
                   flags = 1;
                   break;
               default: /* '?' */
                   fprintf(stderr, "Usage: %s [-a filename]\n",
                           argv[0]);
                   exit(EXIT_FAILURE);
               }
           }

	if(0 == flags)
	{
		openFlags |= O_TRUNC;
		outfile = argv[1];
	}
	else
	{
		openFlags |= O_APPEND;
		outfile = argv[2];
	}

	int filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int outfd = open(outfile,openFlags,filePerms);
	if(-1 == outfd)
	{
		printf("fail to open %s\n",outfile);
		printf("%s\n",strerror(errno));
		exit(-1);
	}
	char readBuf[BUF_SIZE] = {'\0'};
	int readnum;
	while((readnum = read(STDIN_FILENO,readBuf,BUF_SIZE)) > 0)
	{
		write(outfd,readBuf,readnum);
		write(STDOUT_FILENO,readBuf,readnum);
		memset(readBuf,'\0',BUF_SIZE);
	}
	
	if(-1 == close(outfd))
	{
		exit(EXIT_FAILURE);
	}	
	return 0;
}
