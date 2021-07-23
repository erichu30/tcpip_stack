#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

void error (char *msg);

// argc: number of edges, *argv[]: port numbers
int main(int argc, char *argv[]){
    int sock, length, fromlen, n;
    /*        
    include <netinet/in.h> 
    struct sockaddr { 
        unsigned short sa_family;   // 2 bytes address family, AF_xxx 
        char sa_data[14];           // 14 bytes of protocol address 
    }; 
    // IPv4 AF_INET sockets: 
    struct sockaddr_in { 
        short sin_family;           // 2 bytes e.g. AF_INET, AF_INET6 
        unsigned short sin_port;    // 2 bytes port e.g. htons(3490) 
        struct in_addr sin_addr;    // 4 bytes IP address, see struct in_addr, below 
        char sin_zero[8];           // 8 bytes zero to fill in bits
                                    // so as to making length of sockaddr_in and sockaddr equal if needed  
    }; 
    struct in_addr { 
        unsigned long s_addr;       // 4 bytes load with inet_pton() 
    };*/
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buffer[1024];              // sebding and receiving data

    if(argc < 2){
        fprintf(stderr, "Error: port is not provided\n");
        exit(0);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);      // AF_INET: iP address
                                                // SOCK_DGRAM: mark this a datagram-based protocol (UDP)
                                                // 0: default protocol seletced based on previous argument
    
    if(sock<0){             // if anything goes wrong, sock will return a value less than 0
        error("Opening socket ...");
    }

    length = sizeof(server);
    bzero(&server, length);                 // equals to memset
    server.sin_family = AF_INET;            // IPv4 Address Family
    server.sin_addr.s_addr = INADDR_ANY;    // local/server IP or server.sin_addr.s_addr = inet_addr(¡§140.115.65.1¡¨)
    server.sinport = htons(atoi(argv[1]));  // htons: make the integer network format
    
    // bind() assigns a name to a socket
    // int bind(int sockfd, const struct sockaddr *address, socklen_t address_len);
    /* sockfd: the socket assigned the protocol
       address: local address, in sockaddr format
       address_len: length of address */
    if(bind(sock, (struct sockaddr *)&server, length) < 0){
        error("Binding ...");
    }
    fromlen = sizeof(struct sockaddr_in);
    printf("Can strike Ctrl-c to stop Server\n");

    while(1){
        // recvfrom: receive UDP message including client socket address
        // ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
        /* s: socket descriptor
           *buf: pointer point to buffer
           len: buffer size (byte)
           flags: flags set to control how function works
           *from: where the data comes from, in struct sockaddr format
           fromlen: length of sockaddr, it must be initialized first to the size of from or struct sockaddr*/
        n = recvfrom(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&from, &fromlen);
        if(n < 0){
            error("recvfrom...");
        }

        write(1, "Received a datagram: ", 21);
        write(1, buffer, n);

        n = sendto(sock, "This is message from UDP Server\n", 17,
                   0, (struct sockaddr *)&from, fromlen);
        if(n < 0){
            error("sendto failed");
        }
    }
    
    return 0;
}

void error(char *msg){
    perror(msg);
    exit(0);
}
