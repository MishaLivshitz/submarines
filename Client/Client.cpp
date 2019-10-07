#include "Client.h"
#include <sys/types.h>  
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <iostream>

Client::Client(std::string const& a_ip, int a_port)
:m_ip(a_ip)
,m_port(a_port)
,m_socket(-1)
{

}

Client::~Client()
{
    close(m_socket);
}


void Client::Connect() throw (std::runtime_error)
{
    
    
    if( 0 > (m_socket = socket(AF_INET,SOCK_STREAM,0)))
    {
        std::stringstream str;
        str << "Error in clientAccept #" << errno;
		throw std::runtime_error(str.str());
    }
    
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    addr.sin_port = htons(m_port);
    
    if((connect(m_socket,(struct sockaddr*)&addr, sizeof(addr))) < 0)
    {
        std::stringstream str;
        str << "Error in clientAccept #" << errno;
		throw std::runtime_error(str.str());
    }
}
 
size_t Client::Send(Msg const& a_msg) const throw (std::runtime_error)
{
    int sentBytes;

	sentBytes = send(m_socket, &a_msg, sizeof(a_msg), 0);

	if(0 > sentBytes)
	{
		std::stringstream str;
        str << "Error in Send #" << errno;
		throw std::runtime_error(str.str());
	}
	
	return 0;
}

size_t Client::Receive() throw (std::runtime_error)
{
    int sentBytes;
	Msg buffer;
	
	sentBytes = recv(m_socket, &buffer, sizeof(buffer) ,0);
	if(0>sentBytes)
	{
		
        std::stringstream str;
        str << "Error in Receive #" << errno;
		throw std::runtime_error(str.str());
		
	}
	else if(0==sentBytes)
	{
		close(m_socket);
	}
	else
	{		
		std::cout << buffer.m_msg_type << '\n';
		std::cout << buffer.m_sockNumTo << '\n';
		std::cout << buffer.m_sockNumFrom << '\n';
        std::cout << buffer.m_coordinates.first << '\n';
        std::cout << buffer.m_coordinates.second << '\n';
	}
	
	return 0;
}
