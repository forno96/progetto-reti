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
    if((d[0]=='X')|(d[0]=='x')|(d[0]=='Y')|(d[0]=='y')){
        if (d[1]=='('){
            int i=2;
            if (d[2]=='-') i=3;
            if((d[i]=='1')|(d[i]=='2')|(d[i]=='3')|(d[i]=='4')|(d[i]=='5')|(d[i]=='6')|(d[i]=='7')|(d[i]=='8')|(d[i]=='9')|(d[i]=='0')){
                i=i+1;
                while ((d[i]=='1')|(d[i]=='2')|(d[i]=='3')|(d[i]=='4')|(d[i]=='5')|(d[i]=='6')|(d[i]=='7')|(d[i]=='8')|(d[i]=='9')|(d[i]=='0')) {
                    i=i+1;
                }
                if ((d[i]==')')&(d[i+1]=='\0')){
                    return 1;
                } else return 0;
            } else return 0;
        } else return 0;
    } else return 0;
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
    
    //char direzione[512];
    char* direzione = malloc(80*sizeof(char));
    direzione[0]='\0';
    do{
        if (direzione[0]!='\0') {
            printf("Hai inserito una coordinata sbagliata!!\n");
        }
        printf("Inserisci la direzione (X(n) o Y (n)):");
        scanf("%s", direzione);
    } while(check(direzione)!=1);
    
    /*
    printf("Inserisci la direzione (X(n) o Y (n)):");
    scanf("%s", direzione);
    
    int i=0;
    while (direzione[i] != '\0') {
        printf("%d:%c\n",i, direzione[i]);
        i++;
    }
    
    //printf("1: %c , %c\n", direzione[0], direzione[1]);
    while (check(direzione)!=1){
        printf("Hai inserito un carattere errato!!!\nInserisci la direzione (X(n) o Y (n)):");
        scanf("%s", direzione);
        i=0;
        while (direzione[i] != '\0') {
            printf("%d:%c\n",i, direzione[i]);
            i++;
        }
    }
    */
    
    int i=0;
    while (direzione[i] != '\0') {
        printf("%d:%c\n",i, direzione[i]);
        i++;
    }
    
    if ((write(sockfd,direzione,i)) < 0 ) {
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