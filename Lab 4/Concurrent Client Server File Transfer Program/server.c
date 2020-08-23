#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4822
#define LOCALHOST "127.0.0.1"

void clearBuf(char* b){ 
    int i;
    for (i = 0; i < 1024; i++) 
        b[i] = '\0'; 
} 

int main(){
	FILE* fp;
	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int childsoc;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Error creating socket\n");
		exit(1);
	}
	printf("Success\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(LOCALHOST);

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Binding Failed!\n");
		exit(1);
	}
	printf("Success\n");
	listen(sockfd, 10);

	while(1){
		childsoc = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(childsoc < 0)
			exit(1);		
		if((childpid = fork()) == 0){
			while(1){
				clearBuf(buffer);
				recv(childsoc, buffer, 1024, 0);
				printf("\nSending %s file.\n", buffer); 
                fp = fopen(buffer, "r"); 
	            if (fp != NULL) {
				    size_t newLen = fread(buffer, sizeof(char), 1024, fp);
				    fclose(fp);
				}
				printf("Transmission complete!");
				send(childsoc, buffer, strlen(buffer), 0);
				bzero(buffer, sizeof(buffer));
			}
		}
	}
	close(sockfd);
	close(childsoc);
	return 0;
}