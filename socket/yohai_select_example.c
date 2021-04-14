#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 10

int main(int argc, char **argv)
{
	fd_set reads, temps;
	int result;
	char msg[BUFSIZE];
	int str_len;
	struct timeval timeout;

	struct sockaddr_in server1;
	struct sockaddr_in server2;

	int serverfd1 = socket(PF_INET, SOCK_STREAM, 0);
	int serverfd2 = socket(PF_INET, SOCK_STREAM, 0);
	if( serverfd1 == -1 || serverfd2 == -1)
	{
		printf( "server socket 생성 실패\n");
		exit( 1);
	}

	memset( &server1, 0, sizeof(struct sockaddr_in));
	server1.sin_family     = AF_INET;
	server1.sin_port       = htons( 4000);
	server1.sin_addr.s_addr= htonl( INADDR_ANY);

	memset( &server2, 0, sizeof( struct sockaddr_in));
	server2.sin_family     = AF_INET;
	server2.sin_port       = htons( 8000);
	server2.sin_addr.s_addr= htonl( INADDR_ANY);


	FD_ZERO(&reads);
	FD_SET(0, &reads); /* standard input 설정 */

	while (1)
	{
		temps = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		result = select(2, &temps, 0, 0, &timeout);
		if (result == -1) /* select 함수 오류 발생 */
		{
			puts("select error");
			exit(EXIT_FAILURE);
		}
		else if (result == 0) /* timeout */
		{
			puts("time over");
		}
		else
		{
			if (FD_ISSET(0, &temps))
			{
				printf("------\n");
				str_len = read(0, msg, BUFSIZE);
				msg[str_len] = '\0';
				fputs(msg, stdout);
			}
		}
	}
}
