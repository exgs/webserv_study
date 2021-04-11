#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **argv, char **env)
{
	DIR *dir;
	char buf[255] = {0, };
	int ret = 0;
	struct dirent *dirent;

	getcwd(buf, 255);
	printf("%s\n", buf);

	std::cout << "opendir " << std::endl;
	if (NULL == (dir = opendir("./testdir")))
	{
		printf("error\n");
		return (1);
	}
	printf("dir_fd :%d\n", dir->__dd_fd);


	std::cout << "readdir " << std::endl;
	// 디렉토리 포인터를 인자로 받고, 디렉토리 정보를 읽어와 dirent 구조체에 값을 저장한다.
	if (NULL == (dirent = readdir(dir)))
	{
		printf("error\n");
		return (1);
	}
	printf("%s\n", dirent->d_name);
	printf("%d\n", dirent->d_ino);
	printf("%d\n", dirent->d_namlen);
	printf("%c\n", dirent->d_type);

	std::cout << "closedir " << std::endl;
	if (-1 == (ret = closedir(dir)))
	{
		printf("error\n");
		return (1);
	}
	printf("dir_fd :%d\n",dir->__dd_fd); // 값이 바뀜.
}
