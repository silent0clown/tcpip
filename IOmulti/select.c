#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	fd_set reads, temps;
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	FD_ZERO(&reads);   // 初始化fd_set变量
	FD_SET(0, &reads); // 将描述符0对应的位设置为1

	/*
	timeout.tv_sec=5;
	timeout.tv_usec=5000;
	*/

	while(1)
	{
		temps=reads;         // 记住初始值
		timeout.tv_sec=5;    // 在调用select函数前，每次都需要初始化timeval结构体变量
		timeout.tv_usec=0;
		result=select(1, &temps, 0, 0, &timeout);   // 调用select函数。如果有控制台输入数据，则返回大子0的整数;如果没有输入数据而引发超时，则返回0。
		if(result==-1)
		{
			puts("select() error!");
			break;
		}
		else if(result==0)
		{
			puts("Time-out!");
		}
		else 
		{
			if(FD_ISSET(0, &temps)) 
			{
				str_len=read(0, buf, BUF_SIZE);
				buf[str_len]=0;
				printf("message from console: %s", buf);
			}
		}
	}
	return 0;
}