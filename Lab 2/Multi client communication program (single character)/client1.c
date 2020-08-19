#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	
	int fd, temp;
	struct sockaddr_in server;
	struct hostent *host;
	char tosend[10], buff[256];

	fd=socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0){
		printf("Error creating socket");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	host = gethostbyname(argv[1]);
	if(host == 0){
		printf("Hostname error");
		exit(1);
	}
	bcopy((char*)host->h_addr,(char*)&server.sin_addr,host->h_length);

	printf("Enter character: ");
	scanf("%s",tosend);
	int t = sizeof(struct sockaddr_in);
	temp = sendto(fd,tosend,10,0,(struct sockaddr*)&server,t);
	if(temp<0){
		printf("Error Sending");
		exit(1);
	}
	close(fd);
	return 0;
}
