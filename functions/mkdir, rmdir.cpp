#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
	//에러가 나는 경우 파일이 있거나 없거나, 접근권한에 대해서 문제가 될 때,
	int ret;
	ret = mkdir("./hello", 0);
	cout << (ret == 0 ? "suceess" : "error") << endl;

	sleep(1); cout << "wait a minute" << endl;

	ret = rmdir("./hello");
	cout << (ret == 0 ? "suceess" : "error") << endl;
	return (1);
}
