#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

void check(char buffer[], int n){
    

}

int main(int argc, char *argv[]){
    struct sockaddr_in saddr, caddr;
    int sockfd, clen, clientfd;
    unsigned short port = 8784;
    char buffer[256];
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if((sockfd < 0)){
        printf("Error creating socket\n");
        return 1;
    }

    memset(&saddr,0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    if(bind(sockfd, (struct sockaddr *) &saddr,sizeof(saddr)) < 0){
        printf("Error binding");
        return 1;
    }

    if(listen(sockfd,5)<0){
        printf("Error listening\n");
    }
    clen = sizeof(caddr);
    if((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen))<0){
        printf("Error accepting connection \n");
        return 1;
    }
    printf("Connected\n");
    int n=1;
    while(n==1){
        while(buffer[strlen(buffer)-1] != '\n'){
            recv(clientfd,buffer,sizeof(buffer),0);
            printf("Client: %s\n", buffer);
        }
        
        memset(buffer,0,sizeof(buffer));
        while(buffer[strlen(buffer)-1] != '\n'){
            printf("$ ");
            fgets(buffer,256,stdin);
            send(clientfd,buffer,strlen(buffer),0);
        }
              
        memset(buffer,0,sizeof(buffer));

    }
    printf("Good bye!\n");
    close(sockfd);
    close(clientfd);
    return 0;

}