#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "WaitableQueue.h"
#include "Msg.h"
#include "utils.h"
#include <set>

class Server : public UnCopyable
{
public:

    Server(std::string const& a_ip = "127.0.0.1" , int a_port = 8080);
    virtual ~Server();
    void ServerStart() throw (std::runtime_error);
    void clientAccept() throw (std::runtime_error);
    std::set<int> const& clients() const;
    virtual void ServerReceive() throw (std::runtime_error) = 0;
    virtual void ServerSend(int a_sock, Msg const& a_msg) throw (std::runtime_error) = 0;

    //TODO: make them pure!!!

private:
    void listen() const throw (std::runtime_error);
    void getSocket(int a_domain = AF_INET , int a_type = SOCK_STREAM, int a_protocol = 0) throw (std::runtime_error);
    void SetSocketOptions(const void *optval, socklen_t optlen, int level = SOL_SOCKET, int optname = SO_REUSEADDR) const throw (std::runtime_error);
    void bind() const  throw (std::runtime_error);

protected:

    static const int S_BACK_LOG_SIZE = 2;
    std::string m_ip;
    int m_port;
    int m_socket;
    std::set<int> m_clients;

};




#endif