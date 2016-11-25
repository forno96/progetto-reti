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

int check(char d[]){
	int i = 2;
	
	if (d==NULL) return 0;
    if((d[0]!='S')&(d[0]!='s')&(d[0]!='D')&(d[0]!='d')&(d[0]!='A')&(d[0]!='a')&(d[0]!='B')&(d[0]!='b')) return 0;
	if (d[1]!='(') return 0;
	if (d[2]=='-') i=3;
	while ((d[i]=='1')|(d[i]=='2')|(d[i]=='3')|(d[i]=='4')|(d[i]=='5')|(d[i]=='6')|(d[i]=='7')|(d[i]=='8')|(d[i]=='9')|(d[i]=='0'))
		i=i+1;
	if ((i==2)|((i==3) & ((i-1)=='-'))) return 0;
	if (d[i]!=')') return 0;
	if ((d[i+1]!='\0')&(d[i+1]!='\n')&(d[i+1]!='\r')) return 0;
	return 1;
}

int main(int argc, char* argv[]){
	struct sockaddr_in servaddr;
	int listenfd, connfd, errore, lung;
	char buf[MAXLINE];
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
		printf("socket%d\n",listenfd);

	memset(&servaddr,0 , sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));	/* daytime server */
	printf("local address: IP %s port %d\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port) );

	errore = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
		printf("bind%d\n",errore);
	
	errore = listen(listenfd, 10);
		printf("listen%d\n",errore);

	char * str;
	while (1) {
		if (connfd = accept(listenfd, (struct sockaddr *) NULL, NULL)!=-1){
			printf("accept%d\n",connfd);
			if ((lung = read(connfd, buf, sizeof(buf)))<0){
				printf("read%d\n",lung);
			}
			else{
				buf[lung]='\0';
				printf("%s\n",buf);
			
				str = strtok(buf," ");
				while ((str != NULL)&(check(str)!=0)){
					printf("%s\n",str);
					str = strtok(NULL," ");
				}
			}
			close(connfd);
		}
	}
	close(listenfd);
    return 0;
}