#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
 
 
int main()
{
    int fd=0;
    fd = open("demo",O_WRONLY|O_CREAT|O_TRUNC);
    if(fd == -1)
    {
        perror("error open");
        return 1;
    }

    sleep(2);
    unlink("demo");

    char buf[10]="Hello";
	char buf2[10];
    int re = write(fd, buf, 10);
    if(re == 10)
        printf("write ok\n");
    else
        printf("write fail\n");

	// finder에서 확인해보면, 여기서 삭제되는게 보임. 그러나 아래있는 write함수는 정상동작함.
	sleep(5);
	re = read(fd, buf2, 10);
	std::cout << re << std::endl;

	// 넌센스하네...
	re = write(fd, buf, 10);
	std::cout << re << std::endl;

	re = write(15, buf, 10);
	std::cout << re << std::endl;
	close(fd);
	return 0;
}
