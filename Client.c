#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE	512

int main(int argc, char* argv[]){
    if (argc!=3){
        printf("Hai dato un numero sbagliato di argomenti!!\n");
        return 0;
    }
    
	struct sockaddr_in servaddr;
	int sockfd, lung;
	char direzione[MAXLINE];
	char buffer[MAXLINE];
    
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0 ) {
		printf("Errore socket: %d\n",sockfd);
		exit (1);
	}
    
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	
	if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0){//stabilisce la connessione con un server TCP
		printf("Errore connessione\n");
        close(sockfd);
		exit (2);
	}
	
	while(1){
		strcpy(direzione,"\n");
		while(direzione[0] == '\n'){
			printf("Inserisci la direzione (A(n),B(n),S(n),D(n) oppure Q per uscire):");
			fgets(direzione, MAXLINE, stdin);
		}
		direzione[strlen(direzione)-1] = '\0';
		
		if ((strcmp(direzione,"q")==0)||(strcmp(direzione,"Q")==0)) {
			close(sockfd);
			return 0;
		}
        
		if (send(sockfd, direzione, strlen(direzione)+1, 0) < 0){//cerca di scrivere fino a count bytes dal buffer puntato nel buffer di sistema corrispondente al file descriptor fd perché siano poi trasmessi
			printf("Errore send\n");
            close(sockfd);
			exit (3);
		}
		
		if ((lung = recv(sockfd, buffer, MAXLINE, 0))>0){//Si utilizza normalmente con socket connessi perché non consente l'applicazione per recuperare l'indirizzo sorgente dei dati ricevuti
			printf("%s\n",buffer);
		} else {
			printf("Errore recv\n");
            close(sockfd);
			exit (4);
		}
	}
    close(sockfd);//chiude socket
	return 0;
}