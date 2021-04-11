#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void killmyself(int a)
{
	printf("real?\n");
	// exit(EXIT_SUCCESS); // portable codeing style
}
void myhandle(int mysignal)
{
	printf("my handle with signal %d\n", mysignal);
	
	signal(SIGINT, killmyself); //SIGINT에 따른 syscall함수를 변경시킴
}

int main(int argc, char *argv[])
{
	int i = 0;
	signal(SIGINT, myhandle);
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		// signal(SIGINT, myhandle);
		execlp("/usr/bin/grep", "grep", "a", NULL);
		while(1);
		//하나의 프로그램이 동작하는 것이고 이 프로그램에서 CTRL+C 의 의미는 종료
	}
	else
	{
		wait(0);
	}
	// while(1);
	return (0);
}
