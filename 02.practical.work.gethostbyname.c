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
    struct hostent *host_name;
    struct in_addr *address;

    char input[256];
    printf("Enter host domain name: ");
    scanf("%s", input);
    printf("Host name : %s \n",input);

    host_name = gethostbyname(input);
    if (host_name == NULL){
        printf("Invalid host name!\n");
        exit(1);
    }else{
        /*
        address = (struct in_addr *) (host_name->h_addr_list);
        printf("IP address: %s \n", inet_ntoa(*address));
        */
        
        address = (struct in_addr *) (host_name->h_addr);
        printf("IP address: %s \n", inet_ntoa(*address));
        
    }
    return 0;

}