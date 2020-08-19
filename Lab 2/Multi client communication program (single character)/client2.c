#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	
	int fd,temp;
	struct sockaddr_in from;
	int fromlen;
	char recvd[10];

	fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd<0){
		printf("Error creating socket");
		exit(1);
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;

	temp = bind(fd,(struct sockaddr*)&server,sizeof(server));
	if(temp<0){
		printf("Error binding\n");
		exit(1);
	}

	temp = recvfrom(fd,recvd,10,0,(struct sockaddr*)&from,&fromlen);
	if(temp<0){
		printf("Error recieving");
		exit(1);
	}

	printf("Recieved: %c\n\n",recvd[0]);
	close(fd);

	return 0;
}
