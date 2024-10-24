#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>

class EpollServer {

public:
    EpollServer(const char* ip, int port, int maxEvents = 10)
        : ip_(ip), port_(port), maxEvents_(maxEvents) {}

    int run();
private:

    void handleEvent(int epoll_fd, epoll_event& event, int listen_sock);
    
    const char* ip_;
    int port_;
    int maxEvents_;       

};