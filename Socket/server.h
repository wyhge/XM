#pragma once

#include <iostream>
using namespace std;


namespace wyh{
namespace server{

class Server
{

public:
    Server();
    Server(const string &ip, int port);
    virtual ~Server();

    bool bind(const string &ip, int port);
    bool listen(int backlog);
    bool connect(const string &ip, int port);
    bool close();  

protected:
    string  m_ip;
    int     m_port;
    int     m_sockfd;   
};
}
}