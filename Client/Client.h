#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <stdexcept>
#include "Msg.h"
#include "utils.h"

class Client : public UnCopyable
{
public:

    Client(std::string const& a_ip = "127.0.0.1" , int a_port = 8080);
    ~Client();
    void Connect() throw (std::runtime_error);
    virtual size_t Send(Msg const& a_msg) const throw (std::runtime_error);
    virtual size_t Receive() throw (std::runtime_error);
    
    //TODO: make them pure!!!

protected:

    std::string m_ip;
    int         m_port;
    int         m_socket;

};


#endif