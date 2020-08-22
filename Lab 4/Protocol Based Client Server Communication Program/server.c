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

#define PORT 5059

struct mssg{
	char first[10];
	char mid[100];
	char last[30];
};
  
int connection(struct sockaddr_in addr){
    int sockfd,ret;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("Error creating socket!\n");
		exit(1);
	}
	printf("Success\n");
	 
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port =htons( PORT);
	 
	ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    return sockfd;	 
}
int main(){
	 
    struct sockaddr_in addr, cl_addr;
	int sockfd, len, ret, cl1,cl2;
	struct mssg buffer;

	char clientAddr[100];
	sockfd = connection(addr);
	 
	printf("Waiting for connection......\n\n");
	listen(sockfd, 5);
	len = sizeof(cl_addr);
	cl1 = accept(sockfd, (struct sockaddr *) &cl_addr, &len);

	char serc[100];
	memset(&buffer,0,sizeof(buffer));
	read(cl1,&buffer,sizeof(buffer));  
	
	printf("Request from Client:\n%s\n%s\n%s\n\n",buffer.first,buffer.mid,buffer.last);

	char choice;
	choice = buffer.first[4];
	if(choice == '1'){
	   printf("Send Back No: ");
	   scanf("%s",serc);
	}
	else{
	  printf("Send Back Name: ");
	  scanf("%s",serc);
	}
	
	write(cl1,&serc,sizeof(serc));
	close(cl1);
	close(sockfd);
	return 0;
}
