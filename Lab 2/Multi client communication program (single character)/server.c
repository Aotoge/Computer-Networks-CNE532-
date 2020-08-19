#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	
	int fd_from, fd_to;
	struct sockaddr_in server, from, to;
	int fromlen;
	int temp;
	char tosend[10];

	fd_from = socket(AF_INET,SOCK_DGRAM,0);
	if(fd_from<0){
		printf("Error creating socket\n");
		exit(1);
	}

	bzero((void*)&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;

	temp = bind(fd_from,(struct sockaddr*)&server,sizeof(server));
	if(temp<0){
		printf("Error binding\n");
		exit(1);
	}

	temp=recvfrom(fd_from,tosend,10,0,(struct sockaddr*)&from,&fromlen);
	if(temp<0){
		printf("Error Recieving\n");
		exit(1);
	}
	tosend[0]--;

	printf("Sending: %c\n",tosend[0]);
	close(fd_from);
	
	//send portion
	fd_to=socket(AF_INET, SOCK_DGRAM, 0);
	if(fd_to<0){
		printf("Error creating socket");
		exit(1);
	}
	int t = sizeof(struct sockaddr_in);
	to.sin_family = AF_INET;
	to.sin_port = htons(atoi(argv[3]));
	struct hostent *host = gethostbyname(argv[2]);
	if(host == 0){
		printf("Hostname error");
		exit(1);
	}
	bcopy((char*)host->h_addr,(char*)&to.sin_addr,host->h_length);
	temp=sendto(fd_to,tosend,10,0,(struct sockaddr*)&to,t);
	if(temp<0){
		printf("Error Sending");
		exit(1);
	}
	close(fd_to);

	return 0;
}
