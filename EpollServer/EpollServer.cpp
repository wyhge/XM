
#include "EpollServer.h"

int EpollServer::run()
{
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip_, &(serv_addr.sin_addr));
    serv_addr.sin_port = htons(port_);

    if (bind(listen_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Failed to bind socket\n";
        return 1;
    }

    if (listen(listen_sock, 5) < 0) {
        std::cerr << "Failed to listen on socket\n";
        return 1;
    }

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        std::cerr << "Failed to create epoll file descriptor\n";
        return 1;
    }

    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = listen_sock;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_sock, &event)) {
        std::cerr << "Failed to add file descriptor to epoll\n";
        close(epoll_fd);
        return 1;
    }

    while (true) {
        epoll_event events[maxEvents_];
        int num_events = epoll_wait(epoll_fd, events, maxEvents_, 30000);
        for (int i = 0; i < num_events; i++) {
            handleEvent(epoll_fd, events[i], listen_sock);
        }
    }

    close(epoll_fd);
    return 0;
}

void EpollServer::handleEvent(int epoll_fd, epoll_event& event, int listen_sock)
{
    if (event.data.fd == listen_sock) {
            int client_sock = accept(listen_sock, NULL, NULL);
            event.events = EPOLLIN;
            event.data.fd = client_sock;
            if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_sock, &event)) {
                std::cerr << "Failed to add file descriptor to epoll\n";
                close(epoll_fd);
            }
        } else {
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            ssize_t nbytes = read(event.data.fd, buffer, sizeof(buffer));
            if (nbytes == 0) {
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event.data.fd, &event);
                close(event.data.fd);
            } else {
                std::cout << "Received message: " << buffer << std::endl;
                write(event.data.fd, buffer, nbytes);
            }
    }
}