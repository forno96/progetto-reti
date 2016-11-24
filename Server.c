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

int char2int (char A[], int i){
    if (A[i]=='1'){
        return 1;
    } else if (A[i]=='2'){
        return 2;
    } else if (A[i]=='3'){
        return 3;
    } else if (A[i]=='4'){
        return 4;
    } else if (A[i]=='5'){
        return 5;
    } else if (A[i]=='6'){
        return 6;
    } else if (A[i]=='7'){
        return 7;
    } else if (A[i]=='8'){
        return 8;
    } else if (A[i]=='9'){
        return 9;
    } else if (A[i]=='0'){
        return 0;
    } else {
        return -1;
    }
}

int string2int(char A[],int i, int f){
    if (f>=i){
        if (f==i) {
            int a=char2int(A,i);
            if (a==-1) return -1;
            else return a;
        } else {
            int b=char2int(A,f);
            int c=string2int(A,i,f-1);
            if ((b==-1)|(c==-1)) return -1;
            else return (b+(c*10));
        }
    } else return -1;
}

int gapArray(char A[]){
    if(((A[0]=='X')|(A[0]=='x')|(A[0]=='Y')|(A[0]=='y'))&(A[1]=='(')){
        for(int i=2; i<512; i=i+1){
            if (A[i]==')') {
                return (i-1);
            }
        }
        return -1;
    }
    return -1;
}

/*
char int2char(int i){
    if (i==1){
        return '1';
    } else if (i==2){
        return '2';
    } else if (i==3){
        return '3';
    } else if (i==4){
        return '4';
    } else if (i==5){
        return '5';
    } else if (i==6){
        return '6';
    } else if (i==7){
        return '7';
    } else if (i==8){
        return '8';
    } else if (i==9){
        return '9';
    } else if (i==0){
        return '0';
    } else {
        return '\0';
    }
}

void createCor(char[] &A,int x,int y){
    A[0]='[';
    int a,e=x;
    for (int i=1; e>0; i++) {
        a=e
        A[i]=
    }
}
*/

int main(){
    //N.B. L'esempio non usa la funzione fork per far vedere l'utilizzo di
    //     socket non bloccanti
    
    char  buffer[512];
    
    char buffer2[512];
    int buf=0;
    
    int DescrittoreSocket,NuovoSocket;
    int exitCond=0;
    int Quanti, Quanti2;
    int x=0, y=0;
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
                int i;
                if (buffer[2]=='-') {
                    i=-(string2int(buffer,3,gapArray(buffer)));
                    if (i==1) return 1;
                } else {
                    i=string2int(buffer,2,gapArray(buffer));
                    if (i==-1) return 1;
                }
                
                if (buffer[0]=='X'|buffer[0]=='x') {
                    printf("X modificata di %d\n",i);
                    x=x+i;
                } else if (buffer[0]=='Y'|buffer[0]=='y') {
                    printf("Y modificata di %d\n",i);
                    y=y+i;
                } else {
                    printf("Server: Imput Error \n");
                }
                printf("Server: coordinate attuali:[%d,%d] \n",x,y);
                
                /*
                //ritorno del messaggio
                createCor(buffer2,x,y);
                while (buffer2[buf] != '\0') {
                    printf("%c\n", buffer2[buf]);
                    buf++;
                }
                if (write(NuovoSocket, buffer2, sizeof(buffer2)) >0 ){
                    printf("Cordinate inviate al client\n");
                } else {
                    printf("Coordinate non inviate");
                }
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