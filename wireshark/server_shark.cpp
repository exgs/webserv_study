#include <unistd.h>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <netinet/tcp.h>

using namespace std;

int main()
{
	int server_fd;
	int flag;
	socklen_t size;
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "socket 생성 error: %s\n", strerror(errno));
		return -1;
	}
	size = sizeof(flag);
	int opt = 1; // NOTE 여기로 제어가 되긴함.
	int ret ;
	ret = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	cout << ret << endl;
	if(getsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &flag, &size) == -1)
	{
		fprintf(stderr, "socket 생성 error: %s\n", strerror(errno));
		return -1;
	}
	if(flag > 0)
	{
		printf("socket %d는 주소 재사용이 설정된 socket입니다. ", server_fd);
		cout << "flag: " << flag << endl;
	}
	else 
	{
		printf("socket %d는 주소 재사용이 설정되지 않은 socket입니다. ", server_fd);
		cout << "flag: " << flag << endl;
	}

	sockaddr_in	sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // REVIEW 위 아래 어떤 것으로 쓸지
	sockaddr.sin_port = htons(9000); // htons is necessary to convert a number to

	if (bind(server_fd, reinterpret_cast<struct sockaddr*>(&sockaddr), sizeof(sockaddr)) < 0)
	{
		cout << "bind error " << endl;
		return (-1);
	}
	if (listen(server_fd, 5) < 0)
	{
		cout << "listen error" << endl;
	}

	int count= 10000;
	std::string temp_str;
	sockaddr_in	client_sockaddr;
	socklen_t client_sockaddr_len = sizeof(sockaddr_in);
	char buffer[10000 + 1];
	int read_ret;
	int client_fd = accept(server_fd, reinterpret_cast<struct sockaddr*>(&client_sockaddr), &client_sockaddr_len);
	// read_ret = read(client_fd, buffer, count);
	perror("?");
	int sum = 0; // count = 10000
	while ((read_ret = read(client_fd, buffer, count)))
	{
		if (read_ret == -1)
			break;
		cout << "read loop" << endl;
		temp_str.append(buffer, read_ret);
		// close(client_fd);
		// cout << temp_str.length() << endl;
								// 10001747
		if (temp_str.length() > 10000000002)
		{
			// while(1);
			exit(1);
			break ;
		}
	}
	cout << temp_str.length() << endl;
	cout << "close client_fd: " << close(client_fd) << endl;
	cout << "close client_fd: " << close(client_fd) << endl;

	while(1);
}