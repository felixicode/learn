#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 12345

int main(int argc, char **argv)
{
	int server_fd, new_fd, ret;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buf[1024 * 1024], client_ip[64] = {0};

	printf("start\n");

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd <= 0) {
		printf("socket failed\n");
		return 0;
	}
	printf("ok socket\n");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	ret = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	if (ret < 0) {
		printf("bind failed\n");
		close(server_fd);	
		return -1;
	}
	printf("ok bind\n");


	ret = listen(server_fd, 3);
	if (ret < 0) {
		printf("listen failed\n");
		close(server_fd);	
		return -1;
	}
	printf("ok listen\n");


	printf("start accept\n");
	new_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if(new_fd < 0) {
		printf("accept failed\n");
		close(server_fd);	
		return -1;
	}

	inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);

	printf("finish accept, client ip: %s\n", client_ip);

	for (;;) {
		memset(buf, 0, sizeof(buf));
		recv(new_fd, buf, sizeof(buf), 0);
		printf("%s : %s", client_ip, buf);

		fgets(buf, sizeof(buf), stdin);

		send(new_fd, buf, strlen(buf), 0);
	}

	return 0;
}
