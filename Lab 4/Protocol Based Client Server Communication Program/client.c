#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
  
#define PORT 5059
#define LOCAL_HOST "127.0.0.1"
 
struct Message{
	char option[10];
	char reply[100];
	char eot[30];
};

int connection(char **arg,char *serverAddr,struct sockaddr_in addr){
    int sockfd,ret;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
	if (sockfd < 0) {  
	  printf("Error creating socket\n");  
	  exit(1);  
	}  
	printf("Success\n");   

	memset(&addr, 0, sizeof(addr));  
	addr.sin_family = AF_INET;  
	addr.sin_addr.s_addr = inet_addr(serverAddr);
	addr.sin_port = htons(PORT);     

	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
	if (ret < 0) {  
	  printf("Error connecting to the server!\n");  
	  exit(1);  
	}  
	printf("Connected to server\n");  
	return sockfd;
}  

int main(int argc, char**argv) {  
	struct sockaddr_in addr, cl_addr;  
	int sockfd, ret;  
	struct Message buffer; 
	char * serverAddr;
	 // if (argc < 2) {
	 //  printf("usage: client < ip address >\n");
	 //  exit(1);  
	 // }
	 // serverAddr = argv[1]; 

	serverAddr = LOCAL_HOST;
	sockfd = connection(argv,serverAddr,addr);
	 
	memset(&buffer,0,sizeof(buffer));
	char ser_reply[100];
	char num[10]="00001001\0";
	char name[10]="00000001\0";
	bzero(ser_reply,100);
	
	printf("\nChoices:\n");
	printf("1. Name \n");
	printf("2. Number \nEnter Choice: ");

	int choice;
	scanf("%d",&choice);
	
	if(choice == 1)
	   strcpy(buffer.option,name);
	else if(choice == 2)
 	   strcpy(buffer.option,num);
 	else{
 		printf("Incorrect choice\n");
 		exit(1);
 	}

	strcpy(buffer.eot,"--End of Transmission--");
	printf("\nRequest to send: ");
	scanf("%s",buffer.reply);
	//printf("%s\n",buffer[0].m);

	write(sockfd,&buffer,sizeof(buffer));
	read(sockfd,ser_reply,sizeof(ser_reply));
	
	printf("\nServer Reply Received: %s\n",ser_reply);
	close(sockfd);

	return 0;    
} 
