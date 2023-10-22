

#include "server.h"
// using namespace server; 
Server::Server() : m_sockfd(0)
{
    
}

Server::Server(const string &ip, int port) : m_ip(ip), m_port(port), m_sockfd(0)
{
}

Server::~Server()
{
    close();
}
