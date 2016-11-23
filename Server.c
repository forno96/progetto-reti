#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define MAXLINE 99

#include <sys/types.h>
#include <sys/socket.h>
//"in" per "sockaddr_in"
#include <netinet/in.h>
//"fcntl" per la funzione "fcntl"
#include <fcntl.h>

int CreaSocket(int Porta)
{
    int sock,errore;
    struct sockaddr_in temp;
    
    //Creazione socket
    sock=socket(AF_INET,SOCK_STREAM,0);
    //Tipo di indirizzo
    temp.sin_family=AF_INET;
    temp.sin_addr.s_addr=INADDR_ANY;
    temp.sin_port=htons(Porta);
    
    //Il socket deve essere non bloccante
    errore=fcntl(sock,F_SETFL,O_NONBLOCK);
    
    //Bind del socket
    errore=bind(sock,(struct sockaddr*) &temp,sizeof(temp));
    //Per esempio, facciamo accettare fino a 7 richieste di servizio
    //contemporanee (che finiranno nella coda delle connessioni).
    errore=listen(sock,7);
    
    return sock;
}

void ChiudiSocket(int sock)
{
    close(sock);
    return;
}

int main()
{
    //N.B. L'esempio non usa la funzione fork per far vedere l'utilizzo di
    //     socket non bloccanti
    
    char  buffer[512];
    int DescrittoreSocket,NuovoSocket;
    int exitCond=0;
    int Quanti, Quanti2;
    int x=0, y=0;
    int distanza;
    DescrittoreSocket=CreaSocket(1745);
    printf("Server: coordinate attuali:[%d,%d] \n",x,y);
    printf("Server: Attendo connessioni...\n");
    while (!exitCond)
    {
        //Test sul socket: accept non blocca, ma il ciclo while continua
        //l'esecuzione fino all'arrivo di una connessione.
        if ((NuovoSocket=accept(DescrittoreSocket,0,0))!=-1)
        {
            //Lettura dei dati dal socket (messaggio ricevuto)
            if ((Quanti=read(NuovoSocket,buffer,sizeof(buffer)))<0){
                printf("Impossibile leggere il messaggio.\n");
                ChiudiSocket(NuovoSocket);
            }
            else
            {
                //Aggiusto la lunghezza...
                buffer[Quanti]=0;
                //Elaborazione dati ricevuti
                if (buffer[0]=='N'|buffer[0]=='n') {
                    printf("X icrementata di %d\n",1);
                    x=x+1;
                } else if (buffer[0]=='E'|buffer[0]=='e') {
                    printf("Y icrementata di %d\n",1);
                    y=y+1;
                } else if (buffer[0]=='S'|buffer[0]=='s') {
                    printf("X diminuita di %d\n",1);
                    x=x-1;
                } else if (buffer[0]=='O'|buffer[0]=='o') {
                    printf("Y diminuita di %d\n",1);
                    y=y-1;
                } else {
                    printf("Server: Imput Error \n");
                }
                printf("Server: coordinate attuali:[%d,%d] \n",x,y);
                
                /*
                if (strcmp(buffer,"4")==0){
                    printf("Hello World");
                    exitCond=1;}
                else printf("Server: %s \n",buffer);
                */
            }
            //Chiusura del socket temporaneo
            ChiudiSocket(NuovoSocket);
        }
    }
    //Chiusura del socket
    ChiudiSocket(DescrittoreSocket);
    printf("Server: Terminato.\n");
    
    return 0;
}