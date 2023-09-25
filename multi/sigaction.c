#include <stdio.h>
#include <unistd.h>
#include <signal.h>



/*
struct sigaction
{
	void (*sa_handler)(int);         // 信号处理函数指针
	sigset_t sa_mask;                // 为0即可
	int sa_flags;                    // 为0即可
}
*/
void timeout(int sig)
{
	if(sig==SIGALRM)
		puts("Time out!");
	alarm(2);	
}

int main(int argc, char *argv[])
{
	int i;
	struct sigaction act;
	act.sa_handler=timeout;       // 注册handler
	sigemptyset(&act.sa_mask);    // 调用 sigemptyset 函数将 sa_mask成员的所有位初始化为 0 。
	act.sa_flags=0;
	sigaction(SIGALRM, &act, 0);

	alarm(2);

	for(i=0; i<3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}