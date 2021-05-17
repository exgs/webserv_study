#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	// fcntl(pipe1[0], F_SETFL, O_NONBLOCK);
	// fcntl(pipe2[0], F_SETFL, O_NONBLOCK);
	// fcntl(pipe2[1], F_SETFL, O_NONBLOCK);
	// int stdinOfCGI = pipe1[0];
	// int stdoutOfCGI = pipe2[1];
	// int readFdFromCGI = pipe2[0];
	// int writeFdToCGO = pipe1[1];
	write(pipe1[1], "18asdfasdfasdfasdfasdf\n", strlen("18asdfasdfasdfasdfasdf\n"));
	char buf[1000] = {0,};
	int origin_stdoutfd = dup(1);
	int origin_stdinfd = dup(0);
	// printf("! %d\n",origin_stdoutfd);
	int pid = fork();
	if (pid == 0)
	{
		// 1. pipe1의 출구를 STDIN으로 만들자.
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		// dup2(origin_stdinfd, 0);
		// 2. pipe2의 입구를 STDOUT으로 만들자.
		close(pipe2[0]);
		dup2(pipe2[1], 1);
		execve("/Users/ykoh/goinfre/myCGI", 0, 0);
	}
	waitpid(pid, NULL, 0);
	// dup2(origin_stdoutfd, 1);
	read(pipe2[0], buf, sizeof(buf));
	printf("2%s\n", buf);
	close(pipe1[0]);

}