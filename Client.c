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
    int i = 2;
    if((d[0]!='S')&(d[0]!='s')&(d[0]!='D')&(d[0]!='d')&(d[0]!='A')&(d[0]!='a')&(d[0]!='B')&(d[0]!='b')) return 0;
    //printf("1\n");
    if (d[1]!='(') return 0;
    //printf("2\n");
    if (d[2]=='-') {i=3;/*printf("3\n");*/}
    while ((d[i]=='1')|(d[i]=='2')|(d[i]=='3')|(d[i]=='4')|(d[i]=='5')|(d[i]=='6')|(d[i]=='7')|(d[i]=='8')|(d[i]=='9')|(d[i]=='0')) {i=i+1;/*printf("4\n");*/}
    //printf("5\n");
    if ((i==2) | ((i==3)&((d[2])=='-'))) return 0;
    //printf("6\n");
    if (d[i]!=')') return 0;
    //printf("7\n");
    if ((d[i+1]!='\0')&(d[i+1]!='\n')&(d[i+1]!='\r')) return 0;
    //printf("8\n");
    return 1;
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
    
    /* input direzione */
    
    //char* direzione = malloc(80*sizeof(char));
    char * direzione;
    int cilclo=1;
    do{
        if (cilclo!=1) {
            printf("Hai dato un input non corretto!!\n");
        }
        printf("Inserisci la direzione (A(n),B(n),S(n),D(n)):");
        scanf("%ms",&direzione);
        cilclo++;
    } while(check(direzione)!=1);
    
    int i=0;
    while (direzione[i] != '\0') {
        i++;
    }
    
    /* invio direzione */
    if ((write(sockfd,direzione,i)) < 0 ) {
        printf("Errore scrittura: %d\n",errore);
        exit (-3);
    }
    
    // ritorno del messaggio
    char  buffer[512];
    if (read(sockfd,buffer,sizeof(buffer))>0){
        printf("Posizione pedina: %s\n",buffer);
    } else {
        printf("Messaggio non ritornato");
    }
    
    /* ripetizione */
    char flag[1]={'\0'};
    int f=0;
    do{
        if (flag[0]!='\0') printf("%s non è una risposta corretta\n",&flag[0]);
        printf("Vuoi continuare? (Y o N):");
        scanf("%s",&flag[0]);
        f=0;
        while (flag[f] != '\0') {
            f++;
        }
    } while (((f!=1))|((flag[0]!='Y')&(flag[0]!='y')&(flag[0]!='N')&(flag[0]!='n')));
    
    if ((flag[0]=='Y')||(flag[0]=='y')) {
        main(argc,argv);
    }
    free (direzione);
    close(sockfd);
    
    return 0;
}