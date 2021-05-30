#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#define BUFF_SIZE 102400
int main(void)
{
	/* 2. listen socket(듣는 소켓) 을 만들자. */
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == server_socket)
	{
		printf("server socket 생성 실패\n");
		exit(1);
	}
	/* 3. 듣는 소켓 binding 작업 시작 */
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000); // port 번호는 endian 변환
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int value = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) == -1)   
    {
		printf("socketopt error\n");
    }
	if (-1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		printf("bind() 실행 에러\n");
		exit(1);
	}
	/* 4. 듣는 소켓 듣기 */
	if (-1 == listen(server_socket, 5))
	{
		printf("listen() 실행 실패\n");
		exit(1);
	}
	/* ---------------------Accept--------------------- */
	char buff_rcv[BUFF_SIZE + 5];
	char buff_snd[BUFF_SIZE + 5];
	while(1)
	{
		/* 1. client socket(연결 소켓) 을 만들자. */
        struct sockaddr_in client_addr;
		unsigned int client_addr_size = sizeof(client_addr);
		int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
		if (-1 == client_socket)
		{
			printf("클라이언트 연결 수락 실패\n");
			exit(1);
		}
		read(client_socket, buff_rcv, BUFF_SIZE); // 연결 소켓으로 받았다.
		printf("receive: %s\n", buff_rcv);
        std::string buf;
        buf += "HTTP/1.1 301 Moved Permanently\r\n"; 
        buf += "Location: http://afreecatv.com\r\n"; 
        buf += "\r\n"; 
        // localost/oulalala
		write(client_socket, buf.c_str(), buf.length()); // 연결 소켓으로 보냈다.
		close(client_socket);
	}
	return (0);
}