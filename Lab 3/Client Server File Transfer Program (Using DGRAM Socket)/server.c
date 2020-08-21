#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define PORT_NO 4600
#define NET_BUF_SIZE 32 
#define KEY 'K' 

char Encode(char ch){ 
	return ch ^ KEY; 
}

void clearBuf(char* b){ 
	int i; 
	for (i = 0; i < NET_BUF_SIZE; i++) 
		b[i] = '\0'; 
}  

int sendFile(FILE* fp, char* buf, int s){ 
	int i, len; 
	if (fp == NULL) { 
		strcpy(buf, "File doesnt exist"); 
		len = strlen("File doesnt exist"); 
		buf[len] = EOF; 
		for (i = 0; i <= len; i++) 
			buf[i] = Encode(buf[i]); 
		return 1; 
	} 

	char ch, ch2; 
	for (i = 0; i < s; i++) { 
		ch = fgetc(fp); 
		ch2 = Encode(ch); 
		buf[i] = ch2; 
		if (ch == EOF) 
			return 1; 
	} 
	return 0; 
} 

int main(){ 
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = INADDR_ANY; 
	char net_buf[NET_BUF_SIZE]; 
	FILE* fp; 

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);  
    if (sockfd < 0) {
		printf("Error creating socket\n");
		exit(1);
	}
	else
		printf("Success!\n"); 

	if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0) 
		printf("Successfully binded!\n"); 
	else{
		printf("Binding Failed!\n"); 
		exit(1);
	}

	while(1){
		nBytes = 0;
		printf("\nWaiting for request."); 
		clearBuf(net_buf);
		nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, 0, (struct sockaddr*)&addr_con, &addrlen);

		fp = fopen(net_buf, "r"); 
		printf("\nFile Requested: %s", net_buf); 
		if (fp == NULL){
			printf("\nFile open failed."); 
			exit(1);
		}
		else
			printf("\nFile Successfully opened!"); 

		while(1){
			if (sendFile(fp, net_buf, NET_BUF_SIZE)){ 
				sendto(sockfd, net_buf, NET_BUF_SIZE,0,(struct sockaddr*)&addr_con, addrlen); 
				break; 
			}
			sendto(sockfd, net_buf, NET_BUF_SIZE,0,(struct sockaddr*)&addr_con, addrlen); 
			clearBuf(net_buf); 
		} 
		fclose(fp); 
	} 
	return 0; 
} 
