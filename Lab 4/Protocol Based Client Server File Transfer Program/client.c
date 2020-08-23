#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>
  
#define PORT 5200
#define LOCALHOST "127.0.0.1"

struct mssg{
	int no;
	char files[10][100];
};
 
int connection(char *serverAddr,struct sockaddr_in addr){
	int sockfd,ret; 
        sockfd = socket(AF_INET, SOCK_STREAM, 0);  
	if (sockfd < 0) {  
		printf("Error creating socket!\n");  
		exit(1);  
	}  
	printf("Success!\n");   

	memset(&addr, 0, sizeof(addr));  
	addr.sin_family = AF_INET;  
	addr.sin_addr.s_addr = inet_addr(serverAddr);
	addr.sin_port = htons(PORT);     

	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
	if (ret < 0) {  
		printf("Error connecting to the server!\n");  
		exit(1);  
	}  
	return sockfd;
} 

int main(int argc, char**argv){  
	struct sockaddr_in addr, cl_addr;  
	int sockfd, ret;  
	struct mssg buffer[10]; 
	char * serverAddr;
        int n;
        int num[10];
	/*if (argc < 2){
		printf("Enter ip!\n");
		exit(1);  
	}
	serverAddr = argv[1]; */
	serverAddr = LOCALHOST;
	sockfd  = connection(serverAddr,addr);
	printf("Connected to the server\n");  
	bzero(buffer, 10);

	read(sockfd,buffer,sizeof(buffer));
	int ndisp=buffer[0].no,i;
	printf("\nChoose file by number.\nFiles Currently Available:\n");

	for(i=0;i<ndisp;i++){
	  printf("%d. %s\n",i+1,buffer[0].files[i]);
	}	
	scanf("%d",&num[0]);
	write(sockfd,num,sizeof(num));
	char buff[256];
	
	char *recvfile="FileAtClient.txt";
	FILE *fp1=fopen(recvfile,"w");
	bzero(buff,256);
	while(n=recv(sockfd, buff, sizeof(buff),0)>0){
		fputs(buff,fp1);
		bzero(buff,256);
		if(n<255)
			break;
	}
	fclose(fp1);
	close(sockfd);
	return 0;    
} 
