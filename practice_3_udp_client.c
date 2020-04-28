#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 		1234
#define MAXLINE 	1024


int main(int argc, char ** argv) {
	int sockfd;
	char buffer[MAXLINE];
	char *msg = "";
	struct sockaddr_in	 servaddr;

	if (argc > 1){
		msg = argv[1];
	} else{
		printf("Using: ./client 'Start' or ./client 'Stop'\n");
		return 1;
	}

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	} 

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, len;
	sendto(sockfd, (const char *)msg, strlen(msg),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));

	printf("'%s' message sent.\n", msg);

	close(sockfd);
	return 0;
} 
