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

    char hostname[256];
    printf("Enter host domain name: ");
    scanf("%256s", hostname);
    printf("Host name : %s \n",hostname);

    host_name = gethostbyname(hostname);
    if (host_name == NULL){
        printf("Invalid host name!\n");
        exit(1);
    }else{

        for(int i=0; host_name->h_addr_list[i] != NULL; i++){
            // address = (struct in_addr *) (host_name->h_addr_list[i]);
            printf("IP address: %s \n", inet_ntoa(*(struct in_addr *) (host_name->h_addr_list[i])));
        }
        
        
        /*
        address = (struct in_addr *) (host_name->h_addr);
        printf("IP address: %s \n", inet_ntoa(*address));
        */
    }
    return 0;

}