#include <stdio.h>
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

int getaddrinfo(const char *node,                  // e.g "www.example.com" OR IP addr
		const char *service,               // e.g "http", "ftp", or port num
		const struct addrinfo *node_info,  // struct addrinfo of relevant info
		struct addrinfo **res);            // Linked List of Results

int main(int argc, char* argv[]) {

	int status;
	struct addrinfo node_info;
	struct addrinfo *server_info;

	return 0;
}
