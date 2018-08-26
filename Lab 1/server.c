#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	int sockfd, csockfd, portno, clilen;
	char msg[101];
	struct sockaddr_in s_add, c_add;
	int temp;

	sockfd = socket(AF_INET,SOCK_STREAM,0); 
	if(sockfd<0){
		perror("Error opening socket\n");
		exit(1);
	}
	
	bzero((void*)&s_add, sizeof(s_add));
	portno = atoi(argv[1]);

	s_add.sin_family = AF_INET;
	s_add.sin_port = htons(portno);
	s_add.sin_addr.s_addr = INADDR_ANY;

	temp = bind(sockfd, (struct sockaddr*)&s_add,sizeof(s_add));
	if(temp<0){
		perror("Error Binding\n");
		exit(1);
	}

	listen(sockfd,10);
	clilen = sizeof(c_add);

	csockfd = accept(sockfd,(struct sockaddr *) &c_add,&clilen);
	if(csockfd<0){
		perror("Error Accepting\n");
		exit(1);
	}

	bzero(msg,101);	
	temp = read(csockfd, msg, 100);
	if(temp<0){
		perror("Error reading from socket\n");
		exit(1);
	}
	printf("Message Recieved:\n%s\n", msg);

	temp = write(csockfd, "Success!!\n",12);
	if(temp<0){
		perror("Error writing to socket\n");
		exit(1);
	}

	close(sockfd);
	close(csockfd);
	return 0;
}
