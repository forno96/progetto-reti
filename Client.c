#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int check(char d[]){
    if(d[0]!='N'&'n'&'E'&'e'&'S'&'s'&'O'&'o'){
        return(0);
    } else {
        return(1);
    }
}
int main(int argc, char* argv[]){
    struct sockaddr_in servaddr;
    int sockfd, errore;
    
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0 ) {
        printf("Errore socket: %d\n",sockfd);
        exit (-1);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    
    errore = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    if (errore < 0 ) {
        printf("Errore connessione: %d\n",errore);
        exit (-2);
        
    }
    
    char direzione[1];
    int distanza;
    /*
    direzione[0]=' ';
    do{
        if (direzione[0]!=' ') {
            printf("Hai inserito una coordinata sbagliata!!\n");
        }
        printf("Inserisci la direzione (N,E,S,O):");
        scanf("%c",&direzione[0]);
    } while(direzione[0]!='N'&'n'&'E'&'e'&'S'&'s'&'O'&'o');
    */
    
    printf("Inserisci la direzione (N,E,S,O):");
    scanf("%c",&direzione[0]);
    while (direzione[0]!='N'&'n'&'E'&'e'&'S'&'s'&'O'&'o'){
        printf("Hai inserito un carattere errato!!!\nInserisci la direzione (N,E,S,O):");
        scanf("%c",&direzione[0]);
    }
    
    if ((write(sockfd,&direzione[0],1)) < 0 ) {
        printf("Errore scrittura: %d\n",errore);
        exit (-3);
    }
    
    /*
    char prova[20];
    scanf("%s",prova);
    
    errore = write(sockfd,prova,20);
    if (errore < 0 ) {
        printf("Errore scrittura: %d\n",errore);
        exit (-3);
    }
    */
    
    close(sockfd);
    
    return 0;
}