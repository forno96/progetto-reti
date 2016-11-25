#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
//#include <sys/types.h>
//#include <netinet/in.h>
//#include <fcntl.h>
#include <string.h>
#include <unistd.h>
//#include <netdb.h>
#include <arpa/inet.h>

#define MAXLINE	512

int main(int argc, char* argv[]){
	struct sockaddr_in servaddr;
	int sockfd;
	
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0 ) {
		printf("Errore socket: %d\n",sockfd);
		exit (-1);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	
	if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0){
		printf("Errore connessione\n");
		exit (-2);
	}
	
	char direzione[MAXLINE];
	scanf("%[^\t\n]",direzione);
	
	if (direzione == NULL) {
		printf("errore\n");
		exit (-5);
	}
	
	/*if (check(direzione)==0) {
		printf("Error -4");
		exit (-4);
	}*/
	
	
	if (write(sockfd,direzione,strlen(direzione)) < 0){
		printf("Errore scrittura\n");
		exit (-3);
	}

	close(sockfd);
	
	return 0;
}