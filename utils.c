#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#include "utils.h"

void error_check(int res, int sockfd)
{
    if (res == -1) {
        perror("sendto");
        close(sockfd);
        exit(1);
    }
}

struct sockaddr_in init_addr(int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = 0;
    return addr;
}
