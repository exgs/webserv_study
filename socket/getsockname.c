#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

int main()
{
	int connected_fd;
	struct sockaddr_in my_addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	char buffer[16];
	connected_fd = socket( PF_INET, SOCK_STREAM, 0);

	memset(&my_addr, 0, sizeof( my_addr));
	my_addr.sin_family     = AF_INET;
	my_addr.sin_port       = htons( 4000);

	/* 값 변경 하기*/
	my_addr.sin_addr.s_addr= htonl( INADDR_ANY); // 0.0.0.0
	// my_addr.sin_addr.s_addr= inet_addr("127.0.0.1"); // 127.0.0.1
	bind(connected_fd, &my_addr, sizeof(struct sockaddr_in));

	// temp 구조체 만듦
	struct sockaddr_in temp;
	socklen_t temp_len = sizeof(struct sockaddr_in);
	// getsockname으로 값 따오기(int로 ip 주소 따오는 듯)
	if(getsockname(connected_fd, &temp, &temp_len) == -1)
	{
		fprintf(stderr, "getsockname() 호출 error : %s\n", strerror(errno));
		return -1;
	}
	strncpy(buffer, inet_ntoa(temp.sin_addr), 16);
	printf("나의 IP address는 %s입니다.\n", buffer);
}
// 출처: https://www.it-note.kr/120 [IT 개발자 Note]
