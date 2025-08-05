#include <netinet/in.h>
void error_check(int res, int sockfd);
struct sockaddr_in init_addr(int port);
