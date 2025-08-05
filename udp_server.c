#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <stddef.h>

enum { buff_len = 256 };

int main(int argc, char** argv)
{
    if (argc != 2) {
        perror("Usage: ./client [PORT] [IP]\n");
        exit(1);
    }
    const int port = atoi(argv[1]);
    socklen_t addr_len;
    int sockfd, recvfrom_res, bind_res;
    char buff[buff_len];

    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);

    client_addr.sin_addr.s_addr = INADDR_ANY;

    addr_len = sizeof(client_addr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bind_res = bind(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if (bind_res == -1) {
        perror("bind");
        close(sockfd);
        exit(1);
    }
    
    recvfrom_res = recvfrom(sockfd, buff, sizeof(buff), 0, 
                (struct sockaddr*)&client_addr, &addr_len);
    if (recvfrom_res == -1) {
        perror("recvfrom");
        exit(0);
        close(sockfd);
    }
    buff[recvfrom_res] = '\0';
    printf("%s\n", buff);
    close(sockfd);
    return 0;
}
