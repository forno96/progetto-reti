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
	char buffer[MAXLINE];
	int lung;
	
	while(1){
		strcpy(direzione,"\n");
		while(direzione[0] == '\n'){
			printf("Inserisci la direzione (A(n),B(n),S(n),D(n) oppure Q per uscire):");
			//scanf("%[^\n]%*c",direzione);
			fgets(direzione, MAXLINE, stdin);
		}
		direzione[strlen(direzione)-1] = '\0';
		
		if ((strcmp(direzione,"q")==0)||(strcmp(direzione,"Q")==0)) {
			close(sockfd);
			return 0;
		}
		
		if (send(sockfd, direzione, strlen(direzione)+1, 0) < 0){
			printf("Errore send\n");
			exit (-3);
		}
		
		if ((lung = recv(sockfd, buffer, MAXLINE, 0))>0){
			printf("%s\n",buffer);
		}
		else{
			printf("Errore recv\n");
			
		}
	}

	close(sockfd);
	
	return 0;
}