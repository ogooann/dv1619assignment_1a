#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

// Set DEBUG to 1 to enable debugging output
#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <DNS|IPv4|IPv6>:<PORT>\n", argv[0]);
        return 1;
    }

    char *serverAddr = strtok(argv[1], ":");
    char *serverPortStr = strtok(NULL, ":");
    int serverPort = atoi(serverPortStr);

    if (!serverAddr || !serverPort) {
        fprintf(stderr, "Invalid input. Please use the format <DNS|IPv4|IPv6>:<PORT>\n");
        return 1;
    }

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    struct addrinfo hints = {0}, *serverInfo;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(serverAddr, serverPortStr, &hints, &serverInfo) != 0) {
        perror("getaddrinfo");
        return 1;
    }

    if (connect(clientSocket, serverInfo->ai_addr, serverInfo->ai_addrlen) == -1) {
        perror("Connection failed");
        return 1;
    }

    freeaddrinfo(serverInfo);

    // Print minimal information about the connection
    printf("Connected to %s:%d\n", serverAddr, serverPort);

    // Implement the communication with the server here

    close(clientSocket);
    return 0;
}
