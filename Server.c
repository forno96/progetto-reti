#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
//#include <sys/types.h>
//#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
//#include <netdb.h>
#include <arpa/inet.h>

#define MAXLINE	512

int check(char d[]){
	int i = 2;
	printf("uno\n");
	if (strcmp(d,"\0")==0) return 0;
	printf("due\n");
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
	struct sockaddr_in servaddr, client_addr;
	int listenfd, connfd, errore, lung, pid;
	char buf[MAXLINE];
	int len=sizeof(client_addr);
	char * str;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
		printf("socket%d\n",listenfd);

	memset(&servaddr,0 , sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));	/* daytime server */
    //errore=fcntl(listenfd,F_SETFL,O_NONBLOCK);
	printf("local address: IP %s port %d\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port) );

	errore = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
		printf("bind%d\n",errore);
	
	errore = listen(listenfd, 10);
		printf("listen%d\n",errore);

	for( ; ; ){
		strcpy(buf,"\0");
		connfd = accept(listenfd, (struct sockaddr*) &client_addr, &len);
		pid = fork();
		if ( pid !=0 ){
			close ( connfd );
		}
		else {
			close(listenfd);
			while ((lung = recv(connfd, buf, MAXLINE, 0))>0){
				printf("%s\n",buf);/*
				for (str = strtok(buf," "); str != NULL; str = strtok(NULL, " ")){
					puts(str);
					printf("%s",str);
				}
				send(connfd, buf, strlen(buf), 0);*/
				strcpy(buf,"\0");
			}
			close(connfd);
			exit(0);
		}
	}


	/*char * str;
	int clientfd;
		struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);
		clientfd = accept(listenfd, (struct sockaddr*)&client_addr, &addrlen);

		/*---accept a connection (creating a data pipe)---*/
	/*	printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	while ((lung = recv(clientfd, buf, MAXLINE, 0))>0)
	{

		/*---Echo back anything sent---*/
	/*	send(clientfd, buf, lung, 0);

		/*---Close data connection---*//*
	}
		close(clientfd);
	/*
	while ((connfd = accept(listenfd, (struct sockaddr *) NULL, NULL))!=-1) {
		printf("accept%d\n",connfd);
		if ((lung = read(connfd, buf, sizeof(buf)))<0){
			printf("read%d\n",lung);
		}
		else{
			buf[lung]=0;
			printf("%s\n",buf);
			
			for (str = strtok(buf," "); str != NULL; str = strtok(NULL, " "))
{
  puts(str);
  printf("%s",str);
}
			/*str = strtok(buf," ");
			printf("%s\n",buf);
	str = strtok(buf2," ");
	while ((str != NULL)&(check(str)!=0)){
		printf("%s\n",str);
		str = strtok(NULL," ");
	}
			while ((strcmp(str,"\0")!=0)&(check(str)!=0)){
				printf("strtok%s\n",str);
				str = strtok(NULL," ");
			printf("%d\n",strlen(str));
			printf("%c %c %c %c\n",str[0],str[1],str[2],str[3]);
	printf("tre\n");
			}
		}
		close(connfd);
	}*/
	//close(listenfd);
    return 0;
}