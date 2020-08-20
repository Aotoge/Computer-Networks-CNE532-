#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h> 

int main(){

    int sock;
    sock=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4455);
    serverAddr.sin_addr.s_addr =INADDR_ANY;

    if(connect(sock,(struct sockaddr *)&serverAddr,sizeof(serverAddr))== -1 ){
        printf("Error in connection\n ");
    }
    char buffer[1024];

    while(1){
        printf("Data to be sent:\n ");
        fgets(buffer,sizeof(buffer),stdin);
        if (strncmp(buffer, "bye\n", 3) == 0)
            break;
        if(send(sock,&buffer,sizeof(buffer),0) == -1 ){
            printf("Error in sending\n ");
            exit(1);
        }
        if(recv(sock,&buffer,sizeof(buffer),0) == -1){
            printf("Error in recieving\n");
            exit(1);
        }
        printf("Data from server : %s \n",buffer);
    }
    close(sock);
    return 0;
}
