#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define LOCAL_HOST "127.0.0.1"
#define PORT_NO 4600
#define BUF_LEN 32 
#define KEY 'K' 
char *clifile="FileAtClient.txt";

char Decode(char ch){ 
	return ch ^ KEY; 
} 

void clearBuf(char* b){ 
	int i; 
	for (i = 0; i < BUF_LEN; i++) 
		b[i] = '\0'; 
}

int recvFile(char* buf, int s, FILE* fp1){ 
	int i; 
	char ch; 
	for (i = 0; i < s; i++) { 
		ch = buf[i]; 
		ch = Decode(ch); 
		if (ch == EOF) 
			return 1; 
		else{
			printf("%c", ch);
			char s[2];
			s[0]=ch;s[1]='\0';
			fputs(s,fp1);
		}
	} 
	return 0; 
} 

int main(){ 
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr(LOCAL_HOST); 
	char net_buf[BUF_LEN]; 
	FILE* fp; 

	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
  
    if (sockfd < 0){
		printf("Error creating socket\n");
		exit(1);
	}
	else
		printf("Success!\n"); 

	while(1){ 
		printf("\nEnter File Name:"); 
		scanf("%s", net_buf); 
		sendto(sockfd, net_buf, BUF_LEN,0, (struct sockaddr*)&addr_con, addrlen); 
 
		FILE *fp1=fopen(clifile,"w");
		printf("\nData saved at client:\n");
		while (1) { 
			clearBuf(net_buf); 
			nBytes = recvfrom(sockfd, net_buf, BUF_LEN,0, (struct sockaddr*)&addr_con,&addrlen);  
			if (recvFile(net_buf, BUF_LEN,fp1))
				break; 
		}
		printf("EOF-----\n");
		fclose(fp1); 
	} 
	return 0; 
} 
