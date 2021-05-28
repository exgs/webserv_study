#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

#define PORT 9000
#define IPADDR "127.0.0.1"

int main( )
{
	int	c_socket;
	struct sockaddr_in c_addr;
	int	len;
	int	n;
	
	char	rcvBuffer[BUFSIZ];
	
	// 1) 소켓을 생성
	c_socket = socket(PF_INET, SOCK_STREAM, 0);

	// 2) 연결할 서버의 주소 설정
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);		//inet_addr() 는 익숙한 형태의 ip주소를 이진수로 변환해준다
	c_addr.sin_port = htons(PORT);

	// 3) 소켓을 서버에 연결
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr))==-1) {
		printf("Can not connect\n");
		close(c_socket);
		return -1;
	}
	
	
	while (1)
	{
		cout << "write loop" << endl;
		int buf_size = 200;
		char buffer[buf_size];
		memset(buffer, 0, buf_size);
		read(0, buffer, buf_size);
		// dup2(0, c_socket);
		write(c_socket, buffer, strlen(buffer));
	}
	
	/* write로 쓴거 한번에  읽기 */
	char *rcvpointer = rcvBuffer;
	while(0 < (n = recv(c_socket, rcvpointer, 2, 0)))
	{
		rcvpointer += n;
	}
	*rcvpointer = '\0';
	printf("received Data : %s\n", rcvBuffer);
	// 5) 소켓 연결을 종료
	close(c_socket);
}
