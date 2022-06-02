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

int main(int argc, char *argv[]){
    struct sockaddr_in saddr;
    struct in_addr *address;
    struct hostent *h;
    int sockfd;
    unsigned short port = 8784;
    char hostname[256];
    char buffer_send[256];
    char buffer_receive[256];
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
    }
    int n;
    
    return 0;
}