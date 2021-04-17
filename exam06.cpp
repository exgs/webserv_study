#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

void error_exit(char const *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		exit(EXIT_FAILURE);

	std::cout << "helo"	<< std::endl;

	int socket_fd;
	socklen_t len;
	if (0 > (socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
		error_exit("socket_fd error");
	struct sockaddr_in server_addr;
	socklen_t len_sever_addr = sizeof(struct sockaddr_in);
	cout << len_sever_addr << endl;
	// server_addr.sin_family = AF_INET;
	// server_addr.sin_port = htons(atoi(argv[1]));
	// server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// bind(,)

	close(socket_fd);
	return (1);
}
