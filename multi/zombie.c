#include <stdio.h>
#include <unistd.h>

/* 创建僵尸线程 */  
int main(int argc, char *argv[])
{
	pid_t pid=fork();   /* create process */
	
	if(pid==0)     // if Child Process
	{
		puts("Hi I'am a child process");
	}
	else
	{
		printf("Child Process ID: %d \n", pid);
		sleep(30);     // Sleep 30 sec. /* 如果父进程终止，处于僵尸状态的子进程将同时销毁，30s延迟内子进程成为僵尸线程 */
	}

	if(pid==0)
		puts("End child process");
	else
		puts("End parent process");
	return 0;
}
