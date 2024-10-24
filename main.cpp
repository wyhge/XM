#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>  // 添加这一行

#include "EpollServer/EpollServer.h"

int main() {
    printf("main start \n");
    EpollServer server("172.18.211.146", 8888);
    return server.run();

    //return 0;
}