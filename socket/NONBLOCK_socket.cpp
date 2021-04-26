#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int buf_size = 1024;

int main(void)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_socket)
	{
		write(1, "server socket error\n", 20);
		exit(1);
	}
	int value = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) == -1)
	{
		write(1, "server socket opt error\n", 24);
        return (0);
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000); // port 번호는 endian 변환
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (-1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) || errno != 0)
	{
		write(1, "bind error\n", 11);
		exit(1);
	}
	if (-1 == listen(server_socket, 5) || errno != 0)
	{
		write(1, "listen error\n", 13);
		exit(1);
	}

    struct sockaddr_in client_addr;
    memset(&server_addr, 0, sizeof(client_addr));
    unsigned int client_addr_size = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
	// ANCHOR 1. 프로그램을 실행한 뒤에 Postman에서 요청을 보낼 때까지 여기서 BLOCK 됨
	
    if (-1 == client_socket)
    {
        write(1, "client socket error\n", 20);
        exit(1);
    }
	// std::cout << "read size: " << read(client_socket, buff_rcv, buf_size) << std::endl;

	int		read_ret = 0;
	int		sum = 0;

	// ANCHOR 2. 연결된 소켓을 NON_BLOCK 으로 설정을 바꾸어 줌
	int flags = fcntl(client_socket, F_GETFL, 0);
	flags |= O_NONBLOCK;	
	fcntl(client_socket, F_SETFL, flags);

	buf_size = 100000;
    char buff_rcv[buf_size];
	memset(buff_rcv, 0, buf_size);
	// std::cout << "read: " << (read_ret = read(client_socket, buff_rcv, buf_size)) << std::endl;


	// NOTE 3. Postman이 메세지를 보내는 것보다 read 반복문에 먼저 도착하고, NON_BLOCK이기 때문에 기다려주지 않는다.
	char *temp3 = buff_rcv;
	// sleep(1); // NOTE 여기서 잠깐 멈춰주면, 버퍼에 값이 들어간다.
	for (size_t i = 0; i < 10; i++)
	{
		errno = 0;
		if (-1 == (read_ret = read(client_socket, temp3, buf_size/10)))
		{
			std::cout << "-= errno: " << errno << " " << std::strerror(errno) << "=-" << std::endl;
			continue;
		}
		temp3 += read_ret;
	}
	std::cout << "buff_rcv: " << buff_rcv << std::endl;
	// ANCHOR 5. 아무것도 써져있지 않다.
	close(server_socket);
	close(client_socket);
	return (0);
}