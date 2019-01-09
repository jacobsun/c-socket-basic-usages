#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
    char http_header[] = "HTTP/1.1 200 OK \r\n\r\n";
    char response[2048];
    char response_data[1024];

    FILE *html_data;


    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// setup an server address to be connected
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(9000);

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_socket, 4);

    int client_socket;

    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        html_data = fopen("index.html", "r");
        fgets(response_data, 1024, html_data);
        strcat(response, http_header);
        strcat(response, response_data);

        send(client_socket, response, sizeof(response), 0);

        memset(response, 0, sizeof(response));
        close(client_socket);
    }

    return 0;
}
