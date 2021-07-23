#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

void error (char *msg);

int main(int argc, char *argv[]){
    int sock, length, n;
    struct sockaddr_in server;      // the server's full addr
    struct sockaddr_in from;        // address that client uses
    struct hostent *hp;             // holds IP address of server
    char buffer[256];               // holds message from server 

    // Check for proper usage
    if(argc != 3){
        printf("usage: port number\n");
        exit(1);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock<0){             // if anything goes wrong, sock will return a value less than 0
        error("Opening socket ...");
    }

    server.sin_family = AF_INET;    // IPv4 Address Family
    hp = gethostbyname(argv[1]);    // get the host name that is localhost or IP address port I am passing

    if(hp == 0){
        error("Unknown host");
    }
    
    // copy the value
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    // get the port number
    server.sin_port = htons(atoi(argv[2]));
    length = sizeof(struct sockaddr_in);

    bzero(buffer, 256);
    printf("You can enter some message now: ");
    fgets(buffer, 256, stdin);

    n = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&server, length);
    if(n < 0){
        error("sendto failed");
    }

    bzero(buffer, 256);
    n = recvfrom(sock, buffer, 256, 0, (struct sockaddr*)&from, &length);
    if(n < 0){
        error("recvfrom failed");
    }

    printf("Got an ACK from serevr: %s\n", buffer);
    
    return 0;
}

void error(char *msg){
    perror(msg);
    exit(0);
}