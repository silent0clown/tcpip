#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid=fork();
	
	if(pid==0)
	{
		return 3;   	/* 第9行创建的子进程通过return终止 */
	}
	else
	{
		printf("Child PID: %d \n", pid);
		pid=fork();
		if(pid==0)
		{
			exit(7);     /* 第18行创建的子进程通过exit函数终止 */
		}
		else
		{
			printf("Child PID: %d \n", pid);
			wait(&status);  /* 调用 wait函数。之前终止的子进程相关信息将保存到status变量，同时相关子进程被完全销毁 */
			if(WIFEXITED(status))    /* 通过WIFEXITED宏验证子进程是否正常终止。如果正常退出，则调用WEXITSTATUS宏输出子进程的返回值。 */
				printf("Child send one: %d \n", WEXITSTATUS(status));

			wait(&status);        /* 因为之前创建了2个进程，所以再次调用wait函数和宏 */
			if(WIFEXITED(status))
				printf("Child send two: %d \n", WEXITSTATUS(status));
			sleep(30);     // Sleep 30 sec.   /* 为暂停父进程终止而插入的代码 。 此时可以查看子进程的状态 。 */
		}
	}
	return 0;
}