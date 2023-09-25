#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)      // 定义信号处理函数，也称信号处理器(Handler)
{
	if(sig==SIGALRM)
		puts("Time out!");
	alarm(2);	         // 每隔2秒重复产生AIGALRM信号
}
void keycontrol(int sig)  // Handler
{
	if(sig==SIGINT)
		puts("CTRL+C pressed");
}

int main(int argc, char *argv[])
{
	int i;
	signal(SIGALRM, timeout);           // 注册Handler
	signal(SIGINT, keycontrol);         // 注册Handler
	alarm(2);        // 2秒后产生 SIGALRM 信号

	for(i=0; i<3; i++)
	{
		puts("wait...");
		sleep(100);     // 产生信号时，将唤醒由于sleep()而进入阻塞状态的进程，进程一旦被唤醒，就不会再进入睡眠状态。所以该样例运行不到10s就会结束。
	}
	return 0;
}