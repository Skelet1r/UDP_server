#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#include "utils.h"

void error_check(const int res, const int sockfd)
{
    if (res == -1) {
        perror("sendto");
        close(sockfd);
        exit(1);
    }
}

struct sockaddr_in init_addr(const int port, const char* ip)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);
    return addr;
}
