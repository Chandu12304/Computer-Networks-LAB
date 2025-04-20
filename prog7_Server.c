#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netdb.h>

int main(int argc,char *argv[]){
	if(argc < 2){
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int soc = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(atoi(argv[1]));
        
	bind(soc, (struct sockaddr*)&addr, sizeof(addr));
	printf("\nUDP server is established\nwaiting for the client to send the message....\n");

	char buffer[1024];
	ssize_t len = recvfrom(soc, buffer, sizeof(buffer), 0, NULL, NULL);
	buffer[len] = '\0';
	
	printf("\nclient sent the bellow message...\n");
	printf("%s", buffer);
	return 0;
}
