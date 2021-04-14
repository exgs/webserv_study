#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

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
	
	// 4) 서비스 요청과 처리
	if((n = read(c_socket, rcvBuffer, 2)) < 0) 
		return (-1);
	printf("%d\n", n);
	if((n = read(c_socket, rcvBuffer, 2)) < 0) 
		return (-1);
	printf("%d\n", n);
	if((n = read(c_socket, rcvBuffer, 2)) < 0) 
		return (-1);
	printf("%d\n", n);
	if((n = read(c_socket, rcvBuffer, 2)) < 0) 
		return (-1);
	printf("%d\n", n);
	if((n = read(c_socket, rcvBuffer, 2)) < 0) 
		return (-1);
	printf("%d\n", n);
	/* ------------- recv -------------*/
	// if (-1 == (n = recv(c_socket, rcvBuffer, 2, 0)))
	// 	return (-1);
	// printf("%d\n", n);
	// if (-1 == (n = recv(c_socket, rcvBuffer, 2, 0)))
	// 	return (-1);
	// printf("%d\n", n);
	// if (-1 == (n = recv(c_socket, rcvBuffer, 2, 0)))
	// 	return (-1);
	// printf("%d\n", n);
	// if (-1 == (n = recv(c_socket, rcvBuffer, 2, 0)))
	// 	return (-1);
	// printf("%d\n", n);
	// if (-1 == (n = recv(c_socket, rcvBuffer, 2, 0)))
	// 	return (-1);
	// printf("%d\n", n);

	// rcvBuffer[n] = '\0';
	printf("received Data : %s\n", rcvBuffer);
	
	// 5) 소켓 연결을 종료
	close(c_socket);
}
