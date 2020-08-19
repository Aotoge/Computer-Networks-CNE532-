#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

struct data{
	int a;
	char b;
	float c;
};

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

	int a;char b;float c;
	printf("Enter data: ");
	scanf("%d %c %f",&a,&b,&c);
	struct data d;
	d.a=a;d.b=b;d.c=c;
	int t = sizeof(struct sockaddr_in);
	int n = sizeof(struct data);
	temp = sendto(fd,(char*)&d,n,0,(struct sockaddr*)&server,t);
	if(temp<0){
		printf("Error Sending");
		exit(1);
	}
	close(fd);
	return 0;
}
