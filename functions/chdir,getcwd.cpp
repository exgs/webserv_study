/*
자식 프로세스에서 chdir로 경로가 바뀌어도 부모프로세스에 영향을 주지 않음.
독립적이다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *print_pwd()
{
	char buf[255] = {0,};
	getcwd(buf, 255);
	printf("%s\n", buf);
	return NULL;
}

int main(int argc, char **argv, char **env)
{
	int i = 0;
	int child;
	char buf[255] = {0, };
	child = fork();
	print_pwd();
	if (child == 0)
	{
		printf("children \n");
		chdir("..");
		print_pwd();
		exit(0);
	}
	else
	{
		wait(&i);
		printf("parent \n");
		print_pwd(); //변하지 않음
	}
	printf("main \n");
	chdir("..");
	print_pwd(); //변하지 않음
}
