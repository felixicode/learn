#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345 

int main() {
	int sock_fd = 0;
	struct sockaddr_in serv_addr;
	char server_ip[64] = {0}, buf[1024 * 1024] = {0};

	printf("Input server IP:\n");
	scanf("%s", server_ip);

	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error\n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported\n");
		close(sock_fd);
		return -1;
	}

	if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed\n");
		return -1;
	}


	for(;;) {
		fgets(buf, sizeof(buf), stdin);
		send(sock_fd, buf, strlen(buf), 0);
		memset(buf, 0, sizeof(buf));
		recv(sock_fd, buf, sizeof(buf), 0);
		printf("%s :%s", server_ip, buf);
	}

	return 0;
}
