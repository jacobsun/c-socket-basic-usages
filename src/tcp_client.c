#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc, char *argv[]) {
	char request[256] = "Test from 'TCP Client'";
	// socket file descriptor
	int fd;
	// AF_INET: ipv4 family
	// SOCK_STREAM: TCP socket
	// SOCK_DGRAM: UDP socket
	// 0: auto chosen protocol
	fd = socket(AF_INET, SOCK_STREAM, 0);

	// setup an server address to be connected
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(9000);

	int stats = connect(fd, (struct sockaddr *) &server_address, sizeof(server_address));
	if (stats == -1) {
		printf("Error on connect to server");
		return 1;
	}

	send(fd, request, sizeof(request), 0);

	char server_response[256];
	recv(fd, &server_response, sizeof(server_response), 0);

	printf("Got from server: %s\n", server_response);
	// close(fd);

	return 0;
}
