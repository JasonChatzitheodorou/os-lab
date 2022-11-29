#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

int main() {
	char buffer[1024] = {0};
	char ans[1024];

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(49842);
	address.sin_addr.s_addr = INADDR_ANY;
	
	int addrlen = sizeof(address);

	int socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	int bind_id = bind(socket_id, (struct sockaddr *)&address, 16);		
	int l = listen(socket_id, 8);
	int new_socket = accept(socket_id, (struct sockaddr *)&address, (
				socklen_t*)&addrlen);
	int read_val = read (new_socket, buffer, 1024);

	//Read the message and do calculation
	int i = 0;
	int numbers[2];
	char *split_str;
	split_str = strtok (buffer, " ?");
	while(split_str != NULL){
		if (strspn(split_str, "0123456789") == strlen(split_str)) 
			printf("%d\n", numbers[i++] = atoi(split_str));
		if (i == 2) break;
		split_str = strtok(NULL, " ?");
	}
	snprintf(ans, 1024, "%d", numbers[0] + numbers[1]);
	send(new_socket, ans, strlen(ans), 0);
}

	
