#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 		1234
#define MAXLINE 	100000

int main() {
	int sockfd;
	char buffer[MAXLINE];
	char buffer1[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	printf("Hello!\n");

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	} 

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{ 
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	int len, n;
    len = sizeof(cliaddr);
    int cnt = 0;

    while(10){
    	if(cnt >= 10) break;
    	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    	buffer[n] = '\0';

    	sendto(sockfd, (const char *)buffer1, n,
    		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
    		len);
    	cnt++;
    }
    
	return 0;
}