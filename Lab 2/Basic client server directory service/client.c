#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	int sockfd, portno;
	struct sockaddr_in s_add;
	struct hostent *server;
	int temp;
	int data;
	char msg[101];

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("Error creating socket\n");
		exit(1);
	}

	server = gethostbyname(argv[1]);
	if(server == NULL){
		fprintf(stderr, "Error getting host\n");
		exit(1);
	}
	bzero((char*)&s_add,sizeof(s_add));
	s_add.sin_family = AF_INET;
	s_add.sin_port = htons(portno);
	//s_add.sin_addr.s_addr = INADDR_ANY;
	bcopy((char*)server->h_addr,(char*)&s_add.sin_addr.s_addr, server->h_length);

	temp = connect(sockfd,(struct sockaddr*)&s_add,sizeof(s_add));
	if(temp<0){
		perror("Error Connecting\n");
		exit(1);	
	}

	printf("Enter address to be checked: ");
	scanf("%d",&data);
	temp = write(sockfd,(char*)&data,sizeof(data));
	if(temp<0){
		perror("Error writing\n");
		exit(1);
	}
	bzero(msg, 101);
	temp = read(sockfd, msg, 100);
	printf("Matched Name: %s\n", msg);
	close(sockfd);
	return 0;
}
