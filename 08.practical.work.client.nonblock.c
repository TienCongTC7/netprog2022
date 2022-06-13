#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
    struct sockaddr_in saddr;
    struct in_addr *address;
    struct hostent *h;
    int sockfd;
    unsigned short port = 8784;
    char hostname[256];
    char buffer[256];
    printf("Enter host domain name: ");
    scanf("%256s", hostname);
    printf("Host name: %s\n",hostname);

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
    }
    h = gethostbyname(hostname);
    if (h == NULL) {
        printf("Unknown host\n");
    }else{
        address = (struct in_addr *) (h->h_addr);
        printf("IP address: %s\n", inet_ntoa(*address));
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect\n");
        return 1;
    }
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR, &(int){1},sizeof(int));
    int sockf1 = fcntl(sockfd,F_GETFL,0);
    sockf1 |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, sockf1);

    struct pollfd stdin_pollfd;
    stdin_pollfd.fd = fileno(stdin);
    stdin_pollfd.events = POLLIN;

    int finished = 1;
    while(finished==1){
        if(recv(sockfd, buffer, sizeof(buffer),0)>0){
            printf("Server: %s\n", buffer);
            int a = strncmp("dc",buffer,2);
            if(a==0){
                break;
            }
        }
        /*
        while(buffer[strlen(buffer)-1] != '\n'){
            recv(sockfd,buffer,sizeof(buffer),0);
            printf("Server in while: %s\n",buffer);
        }*/
        memset(buffer,0,sizeof(buffer));
        
        if(poll(&stdin_pollfd,1,0)>0){
            if(stdin_pollfd.revents & POLLIN){
                //memset(buffer,0, sizeof(buffer));
                fgets(buffer, 256, stdin);
                int i = strncmp("quit",buffer,4);
                if(i==0){
                    printf("Closing...\n");
                    close(sockfd);
                    break;
                }
                send(sockfd,buffer,strlen(buffer),0);
            }
            memset(buffer,0, sizeof(buffer));
            
            /*while(buffer[strlen(buffer-1) != '\n']){
                fgets(buffer,256,stdin);
                send(sockfd, buffer, sizeof(buffer),0);
                memset(buffer,0,sizeof(buffer));
            }*/
            if(finished){
                printf("$ ");
            }
        }
        
        
      
    }
    printf("Good Bye\n");
    close(sockfd);
    return 0;
}