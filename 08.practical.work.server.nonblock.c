#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

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
    setsockopt(clientfd, SOL_SOCKET, SO_REUSEADDR, &(int){1},sizeof(int));

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
    /*
    if((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen))<0){
        printf("Error accepting connection \n");
        return 1;
    }*/
    struct pollfd stdin_pollfd;
    stdin_pollfd.fd = fileno(stdin);
    stdin_pollfd.events = POLLIN;
    int finished=1;
    while(finished==1){
        clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen);
        if(clientfd > 0){
            printf("Connected\n");
            int client_f1 = fcntl(clientfd, F_GETFL,0);
            client_f1 |= O_NONBLOCK;
            fcntl(clientfd, F_SETFL, client_f1);
            int running = 1;
            while(running){
                if(recv(clientfd,buffer,sizeof(buffer),0)>0){
                    printf("Client: %s\n",buffer);
                }
                /*
                while(buffer[strlen(buffer)-1] != '\n'){
                    recv(clientfd,buffer,sizeof(buffer),0);
                    printf("Client in while: %s\n", buffer);
                    
                }*/
                
                memset(buffer,0,sizeof(buffer));

                if(poll(&stdin_pollfd, 1, 0) > 0){
                    if(stdin_pollfd.revents & POLLIN){
                        printf("$ ");
                        fgets(buffer,256,stdin);
                        send(clientfd,buffer,strlen(buffer),0);
                    }
                }
                /*
                while(buffer[strlen(buffer)-1] != '\n'){ 
                        printf("$ ");
                        fgets(buffer,256,stdin);
                        send(clientfd,buffer,strlen(buffer),0);
                }*/
                memset(buffer,0,sizeof(buffer));
                
            }
            close(clientfd);
        }

    }
    printf("Good bye!\n");
    close(sockfd);
    close(clientfd);
    return 0;

}