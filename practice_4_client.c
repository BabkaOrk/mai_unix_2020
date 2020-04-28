#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>  


#define PORT 		1234
#define MAXLINE 	100000
char m[1024] = {0};

int main(int argc, char ** argv) {
	int sockfd;
	int len_msg = 0;
	char buffer[MAXLINE];
	char *msg = "";
	struct sockaddr_in	 servaddr;

	if (argc > 1){
		len_msg = atoi(argv[1]);
	} else{
		printf("Using: ./client 'size'\n");
		return 1;
	}

	char *a;
	a = (char*)calloc(len_msg, sizeof(char));


	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	} 

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	int n, len;
	struct timespec mt1, mt2; 
	long int tt, sum, max, min = 100000000000;
	
    int cnt = 0;
    while(1){
    	if(cnt >= 10) break;
    	clock_gettime (CLOCK_REALTIME, &mt1);

    	sendto(sockfd, (const char *)a, len_msg, 
    		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
    		sizeof(servaddr)); 

    	n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
    		MSG_WAITALL, (struct sockaddr *) &servaddr, 
    		&len);

    	clock_gettime (CLOCK_REALTIME, &mt2);

    	printf("Server : %d\n", n);
    	tt=1000000000*(mt2.tv_sec - mt1.tv_sec)+(mt2.tv_nsec - mt1.tv_nsec);
    	printf ("Затрачено время: %ld нс\n",tt);

    	if(tt > max) max = tt;
    	if(tt < min) min = tt;
    	sum+=tt;
    	sleep(2);
    	cnt++;
    }

	sum = sum/cnt;
	printf("\n\nПакет: %d байт\n", len_msg);
	printf("Минимальное время: %ld нс\n", min);
	printf("Среднее время: %ld нс\n", sum);
	printf("Максимальное время: %ld нс\n", max);

	close(sockfd);
	return 0;
} 
