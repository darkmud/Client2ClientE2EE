#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <netdb.h>       
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define BACKLOG 2

using namespace std;

// 2 individual clients, client 1 sends to server, server sends to client 2, client 2 responds to server, server sends to client 1

int main(int argc, char* argv[]) {
    int status, sockfd, clientfd;
    struct addrinfo hints, *server;
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof client_addr;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ( (status = getaddrinfo(NULL, "80", &hints, &server)) != 00) {
        std::cerr << "getaddrinfo() error: " << gai_strerror(status);
    }

    if ( (sockfd = socket(server -> ai_family, server -> ai_socktype, server -> ai_protocol)) == -1) {
        std::cerr << "Socket Error";
    }

    if (bind(sockfd, server -> ai_addr, server -> ai_addrlen) == -1) {
        close(sockfd);
        std::cerr << "Bind Error";
    }

    freeaddrinfo(server);

    if (listen(sockfd, BACKLOG) == -1) {
        std::cerr << "Listen Error";
        exit(1);
    }
   
    if ( (clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &addr_size)) == -1) {
        std::cerr << "Accept Error";
    } else {
        std::cout << "Server Connected to Client.";
    }

    return 0;
}
