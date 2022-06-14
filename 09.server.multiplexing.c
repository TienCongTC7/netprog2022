#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in saddr, caddr;
    int sockfd, clen, clientfd;
    unsigned short port = 8784;
    char buffer[256];
    int client_array[100];
    memset(client_array,0, sizeof(client_array));
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
    while(finished==1)
    {
        fd_set set;     // declaration of the set
        FD_ZERO(&set);  // clear the set
        FD_SET(sockfd,&set);    // add listening socket to set
        int maxfd= sockfd;
        for(int i=0; i < 100; i++)
        {
            if(client_array[i] > 0)
            {
                //add connected client sockets into set
                FD_SET(client_array[i],&set);
                if (client_array[i] > maxfd)
                {
                    maxfd = client_array[i];    
                }
            }
        }
        // poll and wait, blocked indefinitely
        select(maxfd + 1, &set, NULL, NULL, NULL);
        
        if(FD_ISSET(sockfd,&set))
        {
            clientfd = accept(sockfd, (struct sockaddr *) &saddr, &clen);
            if(clientfd > 0)
            {
                printf("Connected\n");
                int client_f1 = fcntl(clientfd, F_GETFL,0);
                client_f1 |= O_NONBLOCK;
                fcntl(clientfd, F_SETFL,client_f1);
                // add to the client array
                for(int i=0; i < 100; i++)
                {
                    if(client_array[i] == 0)
                    {
                        client_array[i] = clientfd;
                        break;
                    }
                }
            }
        }
        
        for(int i=0 ; i < 100; i++){
            if(client_array[i] > 0 && FD_ISSET(client_array[i], &set))
            {
                if(recv(clientfd,buffer,sizeof(buffer),0)>0)
                {
                    printf("client %d says: %s \nserver>$",i,buffer);
                    memset(buffer, 0, sizeof(buffer));
                }
                else
                {
                    printf("client %d has disconnected. \n",client_array[i]);
                    client_array[i]  = 0;
                }
                if (poll(&stdin_pollfd,1,0)>0)
                {
                    if (stdin_pollfd.revents & POLLIN)
                    {
                        fgets(buffer, 256, stdin);
                        send(clientfd, buffer, strlen(buffer),0);g
                        memset(buffer, 0, sizeof(buffer));
                    }
                }
            }
        }
        /*
        int running = 1;
        while (running)
        {
            if (recv(clientfd, buffer, sizeof(buffer), 0) > 0)
            {
                printf("Client: %s\n", buffer);
            }

            memset(buffer, 0, sizeof(buffer));
            if (poll(&stdin_pollfd, 1, 0) > 0)
            {
                if (stdin_pollfd.revents & POLLIN)
                {
                    printf("$ ");
                    fgets(buffer, 256, stdin);
                    send(clientfd, buffer, strlen(buffer), 0);
                }
            }
            if (running)
            {
                printf("$ ");
            }
        }*/
        //close(clientfd);
    }

    printf("Good bye!\n");
    close(sockfd);
    close(clientfd);
    return 0;
}

