#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct datum{
	int code;
	char matched_name[100];
} database;

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
	int input_code;
	temp = read(csockfd, (char*)&input_code, 100);
	int i,f=0;

	FILE *fptr;
	database record;
	if ((fptr = fopen("directory.txt","r")) == NULL){
       printf("Error opening file");
       exit(1);
	}
	
	while(fread(&record, sizeof(database), 1, fptr) == 1){
		if(record.code==input_code){
			f++;
			break;
		}
	}
	
	fclose(fptr);

	if(f==0)
		temp = write(csockfd, "Address not found\n",18);
	else{
		char buf[100];
		strcpy(buf,record.matched_name);
		temp = write(csockfd,buf,sizeof(buf));
	}
	if(temp<0){
		perror("Error writing to socket\n");
		exit(1);
	}

	close(sockfd);
	close(csockfd);
	return 0;
}
