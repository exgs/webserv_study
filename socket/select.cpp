#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

// https://yms2047.tistory.com/entry/select-%ED%95%A8%EC%88%98-%EC%82%AC%EC%9A%A9%EB%B2%95

int main()
{
	const char *str = "hello\n";
	write(1, str, strlen(str));
	fd_set set;
	FD_ZERO(&set);
	int fd = open("select.txt", O_RDWR | O_TRUNC, 0755);
	int sum = 0;
	FD_SET(fd, &set);
	
	timeval time;
	int ret;
	while (1)
	{
		sum++;
		time.tv_sec = 2;
		time.tv_usec = 0;
		if(true)
			FD_SET(fd, &set);
		if(0 == (ret = select(4, NULL, &set, NULL, &time)))
		{
			std::cerr << "timeout\n" ;
			FD_SET(fd, &set);
		}
		else if (ret == -1)
		{
			std::cerr << "-1\n" ;
		}
		else if (ret > 0)
		{
			write(fd, "Test_end\n",9);
			std::cerr << "2\n" ;
			FD_CLR(fd, &set);
		}
		sleep(1);
	}
	return (1);
}