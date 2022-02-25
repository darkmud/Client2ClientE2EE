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


// FUNCTION DECLARATIONS
int getaddrinfo(const char *node,          // e.g "www.example.com" OR IP addr
		const char *service,               // e.g "http", "ftp", or port num
		const struct addrinfo *node_info,  // struct addrinfo of relevant info
		struct addrinfo **res);            // Linked List of Results

int socket(int domain, int type, int protocol);
int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int send(int sockfd, const void *msg, int len, int flags);
int recv(int sockfd, void *buf, int len, int flags);
int shutdown(int sockfd, int how);

int getpeername(int sockfd, struct sockaddr *addr, int *addrlen);
int gethostname(char *hostname, size_t size);

using namespace std;

/*
// sockfd_create() => Uses getaddrinfo() and socket() to create a Socket Descriptor
int sockfd_create(char *address, char *port) {
    int status;
    struct addrinfo node_info, *server_info;

    memset(&node_info, 0, sizeof node_info);
    node_info.ai_family = AF_UNSPEC;
    node_info.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(address, port, &node_info, &server_info);

    //print_ip(server_info); 

    freeaddrinfo(server_info);
    return 0;
}*/

// print_ip() => Prints out IP Address
void print_ip(const struct addrinfo *server_info) {
    void* addr;
    char ipstr[INET_ADDRSTRLEN];

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)server_info -> ai_addr;
    addr = &(ipv4 -> sin_addr);
    inet_ntop(AF_INET, addr, ipstr, sizeof ipstr);
    cout << "IPV4: " << ipstr << endl;
}

class Socket
{
    public:
    int status, sockfd;

    int sockfd_create(char *address, char *port) {
        int status;
        struct addrinfo node_info, *server_info;

        memset(&node_info, 0, sizeof node_info);
        node_info.ai_family = AF_UNSPEC;
        node_info.ai_socktype = SOCK_STREAM;

        status = getaddrinfo(address, port, &node_info, &server_info);
        
        print_ip(server_info);

        freeaddrinfo(server_info);
        return 0;
    }
};

// MAIN
int main(int argc, char *argv[]) {

    int status, sockfd;

	if(argc != 2) {
        std::cout <<"Usage: ./serverstart showip <hostname>";	
	}

    //sockfd = sockfd_create(argv[1], NULL);
    //cout << sockfd;

    Socket sock1;
    sock1.sockfd_create(argv[1], NULL);


	return 0;
}
