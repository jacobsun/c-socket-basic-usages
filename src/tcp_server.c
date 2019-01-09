#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
    char response[256] = "Got your message.";

    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);

	// setup an server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(9000);

    // give the address to the fd
    bind(fd, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(fd, 3);

    int client_fd;
    client_fd = accept(fd, NULL, NULL);

	char client_request[256];
    int recv_len;
	recv_len = recv(fd, &client_request, sizeof(client_request), 0);
    if (recv_len == -1) {
        printf("Recieve client message error.");
    } else if (recv_len == 0) {
        printf("Recieve nothing.");
    } else {
        printf("Got Client request: %s", client_request);
    }

    send(client_fd, response, sizeof(response), 0);

    // close(fd);
}
