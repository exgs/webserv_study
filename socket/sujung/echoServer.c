#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"

static const int MAXPENDING = 5;

void	HandleTCPClient(int clntSocket);

int		main(int argc, char **argv) {
	if (argc != 2)
		DieWithUserMessage("Parameter(s)", "<Server Port>");

	in_port_t servPort = atoi(argv[1]);

	// 연결 요청을 처리하는 소켓 생성
	int servSock; // 서버 소켓 식별자
	if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithSystemMessage("socket() failed");
	// 지역 주소 구조체 생성
	struct sockaddr_in	servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(servPort);

	// 지역 주소에 바인드
	if (bind(servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		DieWithSystemMessage("bind() failed");

	if (listen(servSock, MAXPENDING) < 0)
		DieWithSystemMessage("listen() failed");

	for (;;) { // 무한 실행
		struct sockaddr_in clntAddr;
		socklen_t clntAddrlen = sizeof(clntAddr);

		// 클라이언트의 연결을 기다림
		int clntSock = accept(servSock, (struct sockaddr *) &clntAddr, &clntAddrlen);
		if (clntSock < 0)
			DieWithSystemMessage("accept() failed");

		char clntName[INET_ADDRSTRLEN]; // 클라이언트 주소를 담기 위한 문자열
		if (inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
			printf("Handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
		else
			puts("Unable to get client address");

		HandleTCPClient(clntSock);
	}
}

void	HandleTCPClient(int clntSocket) {
	char buffer[BUFSIZ];

	ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZ, 0);
	if (numBytesRcvd < 0)
		DieWithSystemMessage("recv() failed");

	while (numBytesRcvd > 0) {
		ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
		if (numBytesSent < 0)
			DieWithSystemMessage("send() failed");
		else if (numBytesSent != numBytesRcvd)
			DieWithUserMessage("send()", "sent unexpected number of bytes");

		numBytesRcvd = recv(clntSocket, buffer, BUFSIZ, 0);
		if (numBytesRcvd < 0)
			DieWithSystemMessage("recv() failed");
	}

	close(clntSocket);
}
