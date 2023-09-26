#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds[2];
	char str[]="Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;
	
	pipe(fds);          // pipe函数创建管道,fds数组中保存用于I/O的文件描述符
	pid=fork();         // 父子进程同时拥有管道
	if(pid!=0)
	{
		read(fds[0], buf, BUF_SIZE);          // 父进程接收管道信息
		puts(buf);
	}
	else
	{
		write(fds[1], str, sizeof(str));      // 子进程写入管道信息
	}
	return 0;
}