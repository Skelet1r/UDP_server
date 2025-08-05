#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <stddef.h>

int main(int argc, char** argv)
{
    if (argc != 3) {
        perror("Usage: ./client [PORT] [MESSAGE]\n");
        exit(1);
    }
    const int port = atoi(argv[1]);
    const char* message = argv[2];
    const size_t message_size = strlen(message);

    int sockfd, sendto_res;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sendto_res = sendto(sockfd, message, message_size, 0, 
                (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (sendto_res == -1) {
        perror("sendto");
        close(sockfd);
        exit(1);
    }
    close(sockfd);
    return 0;
}
