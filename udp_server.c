#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <stddef.h>

#include "utils.h"

enum { buff_len = 256 };

static void send_message(const int sockfd, int sending_data, int* datagrams_count, struct sockaddr_in* client_addr)
{
    const int size_of_sending_data = sizeof(sending_data);
    int send_res;
    send_res = sendto(sockfd, &sending_data, size_of_sending_data, 0,
                            (struct sockaddr*)client_addr, sizeof(*client_addr));
    error_check(send_res, sockfd);
    ++*datagrams_count;
}

static void recv_message(int sockfd, int* buff_size, struct sockaddr_in* client_addr)
{
    char buff[buff_len];
    int recvfrom_res;
    socklen_t addr_len;

    addr_len = sizeof(*client_addr); 
    recvfrom_res = recvfrom(sockfd, buff, sizeof(buff), 0, 
                (struct sockaddr*)client_addr, &addr_len);
    error_check(recvfrom_res, sockfd);
    *buff_size += recvfrom_res;
}

static void bind_socket(int sockfd, struct sockaddr_in* client_addr)
{
    int bind_res;
    bind_res = bind(sockfd, (struct sockaddr*)client_addr, sizeof(*client_addr));
    error_check(bind_res, sockfd);
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        perror("Usage: ./client [PORT] [IP]\n");
        exit(1);
    }
    const int port = atoi(argv[1]);
    int datagrams_count, buff_size;
    datagrams_count = 0;

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addr_len;
        int sockfd, recvfrom_res, bind_res, send_dg_count_res, send_buff_size_res;

        client_addr = init_addr(port);
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        
        bind_socket(sockfd, &client_addr);

        recv_message(sockfd, &buff_size, &client_addr);

        send_message(sockfd, datagrams_count, &datagrams_count, &client_addr);
        send_message(sockfd, buff_size, &datagrams_count, &client_addr);

        close(sockfd);
    }
    return 0;
}
