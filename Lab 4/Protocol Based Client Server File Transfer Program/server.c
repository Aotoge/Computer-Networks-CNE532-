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

struct Message{
   int no;
   char files[10][100];
};
  
int connection(struct sockaddr_in addr){
        int sockfd,ret;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("Error creating socket\n");
		exit(1);
	}
	printf("Success!\n");
	 
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port =htons(PORT);	 
	ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	return sockfd;
}

int main(){	
	struct sockaddr_in addr, cl_addr;
	int sockfd, len, ret, cl1,cl2;
	struct Message buffer[10];
	char clientAddr[100];	 
	sockfd = connection(addr);

	printf("Waiting For Connection\n");
	listen(sockfd, 5);


	len = sizeof(cl_addr);
	cl1 = accept(sockfd, (struct sockaddr *) &cl_addr, &len);


	char file1[20]="sample1.txt\0";
	char file2[20]="sample2.txt\0";
	char file3[20]="sample3.txt\0";

	int num[10];
	bzero(buffer, 10);
	bzero(num,10);
	strcpy(buffer[0].files[0],file1);
	strcpy(buffer[0].files[1],file2);
	strcpy(buffer[0].files[2],file3);
	buffer[0].no=3;

	write(cl1,buffer,sizeof(buffer));
	read(cl1,num,sizeof(num));

	int k=num[0]-1;
	printf("Client requested for %s.\n",buffer[0].files[k]);
	char sendfile[100];
	strcpy(sendfile,buffer[0].files[k]);

	FILE *fp=fopen(sendfile,"r");
	char buf[256];
	bzero(buf,256);

	 while ( fgets ( buf, 255, fp ) != NULL ){
		write(cl1, buf, sizeof(buf));
		bzero(buf,256);
	}
	fclose (fp);
	printf("File sent successfully!!\n");
	close(cl1);
	close(sockfd);
	return 0;
}
