#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>   //===================
#include <sys/socket.h>  // For getaddrinfo()
#include <netinet/in.h>  //
#include <netdb.h>       //===================

#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define BACKLOG 10

using namespace std;

// print_ip() => Prints out IP Address
void print_ip(int ip_ver, const struct addrinfo *server_info) {
    void* addr;

    if (ip_ver == 4) {
        char ipstr[INET_ADDRSTRLEN];
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)server_info -> ai_addr;
        addr = &(ipv4 -> sin_addr);
        inet_ntop(AF_INET, addr, ipstr, sizeof ipstr);
        cout << "IPV4: " << ipstr << endl;
    }
    /*} else if (ip_ver == 6) {
        char ipstr[INET6_ADDRSTRLEN];
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)server_info -> ai_addr;
        addr = &(ipv6 -> sin6_addr);
        inet_ntop(AF_INET6, addr, ipstr, sizeof ipstr);
        cout << "IPV6: " << ipstr << endl;
    }*/
}

class Socket
{
    public:
    int status, sockfd;

    int sockfd_connect(char *address, char *port) {
        int status;
        struct addrinfo node_info, *server_info;

        memset(&node_info, 0, sizeof node_info);
        node_info.ai_family = AF_UNSPEC;
        node_info.ai_socktype = SOCK_STREAM;

        if ((status = getaddrinfo(address, port, &node_info, &server_info)) != 0) {
            std::cerr << "getaddrinfo() ERROR: " << gai_strerror(status);
            return 2;
        }

        if ( (sockfd = socket(server_info -> ai_family, server_info -> ai_socktype, server_info -> ai_protocol)) == -1) {
            perror("Socket Error");
        }

        bind(sockfd, server_info -> ai_addr, server_info -> ai_addrlen); 
        
        if (connect(sockfd, server_info -> ai_addr, server_info -> ai_addrlen) == -1) {
            perror("Connection Error");
        }

        listen(sockfd, BACKLOG);

        int new_fd;
        struct sockaddr_storage their_addr;
        socklen_t addr_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

        char const *msg = "test";
        int len, bytes_sent;
        len = strlen(msg);
        bytes_sent = send(sockfd, msg, len, 0);

        print_ip(4, server_info);

        freeaddrinfo(server_info);
        return 0;
    }
};

// MAIN
int main(int argc, char *argv[]) {

    Socket sock1;
    int status, sockfd;

	if(argc != 3) {
        std::cout <<"Usage: ./serverstart showip <hostname> <port>";	
	}

    sock1.sockfd_connect(argv[1], argv[2]);

	return 0;
}
