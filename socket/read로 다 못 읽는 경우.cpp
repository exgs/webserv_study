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

	std::cout << "1" << std::endl;
	if (-1 == client_socket)
	{
		write(1, "client socket error\n", 20);
		exit(1);
	}
	int		read_ret = 0;
	buf_size = 30000000; //300MB
	char *buff_rcv = (char *)malloc(buf_size * sizeof(char));
	memset(buff_rcv, 0, buf_size);

	// ANCHOR read() NON_BLOCKING
	int flags = fcntl(client_socket, F_GETFL, 0);
	flags |= O_NONBLOCK;	
	fcntl(client_socket, F_SETFL, flags);
	usleep(1);

	// ANCHOR read() BLOCKING
	errno = 0;
	std::cout << "read: " << (read_ret = read(client_socket, buff_rcv, buf_size)) << std::endl;
	std::cout << "-= errno: " << errno << " " << std::strerror(errno) << " =-" << std::endl;
	close(server_socket);
	close(client_socket);
	return (0);
}