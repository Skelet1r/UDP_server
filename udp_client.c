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

    socklen_t addr_len;
    int sockfd, sendto_res, recv_dg_count_res, recv_buff_size_res, dg_count, buff_size;

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
    
    addr_len = sizeof(server_addr);
    recv_dg_count_res = recvfrom(sockfd, &dg_count, sizeof(dg_count), 0,
                                    (struct sockaddr*)&server_addr, &addr_len);
    if (recv_dg_count_res == -1) {
        perror("recvfrom");
        close(sockfd);
        exit(1);
    }
     
    recv_buff_size_res = recvfrom(sockfd, &buff_size, sizeof(buff_size), 0,
                                    (struct sockaddr*)&server_addr, &addr_len);
    if (recv_buff_size_res == -1) {
        perror("recvfrom");
        close(sockfd);
        exit(1);
    }
    printf("Datagrams count: %d\nDatagrams total size: %d\n", dg_count, buff_size);
    close(sockfd);
    return 0;
}
