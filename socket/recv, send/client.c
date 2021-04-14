//pingpong client
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#define SA  struct sockaddr_in

int main()
{
	const int port = 80;

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	SA addr;

	char buffer[2048];
	int recv_len;
	int send_len;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sock, (struct sockaddr*)&addr, sizeof(SA)) == -1) {
		fprintf(stderr, "Connect Error : %s\n", strerror(errno));
		return(-1);
	}
	else printf("connected\n");

	//Make send message
	for (int i = 0; i < 50;)
	{
		for (int j = 0; j < 10; j++, i++)
			buffer[i] = 'a' + j;
	}
	printf("client: %s\n", buffer);

	while ((send_len = send(sock, buffer, 2, 0)) != -1) {
		if (errno == EINTR) {
			continue;
		}
		// else {
		// 	fprintf(stderr, "Send Error : %s\n", strerror(errno));
		// 	return -1;
		// }
	}

	while ((recv_len = recv(sock, buffer, 256, 0)) == -1) {
		if (errno == EINTR) {
			continue;
		}
		else {
			fprintf(stderr, "Recv Error : %s\n", strerror(errno));
			return -1;
		}
	}

	printf("%s\n", buffer);
}
