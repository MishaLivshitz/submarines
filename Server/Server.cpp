
#include "Server.h"

#include <arpa/inet.h>
#include <cstring>
#include <sstream>
#include <cerrno>

Server::Server(std::string const& a_ip, int a_port)
:m_ip(a_ip)
,m_port(a_port)
,m_socket(-1)
{

}

Server::~Server()
{

}

void Server::getSocket(int a_domain , int a_type, int a_protocol) throw (std::runtime_error)
{
    m_socket = socket(a_domain, a_type, a_protocol);
	if(m_socket < 0)
	{
        std::stringstream str;
        str << "Error in getSocket #" << errno;
		throw std::runtime_error(str.str());
	}
}

void Server::SetSocketOptions(const void *optval, socklen_t optlen, int level, int optname) const throw (std::runtime_error)
{
    if((setsockopt(m_socket, level, optname, &optval, sizeof(optval))) < 0)
	{
		std::stringstream str;
        str << "Error in SetSocketOptions #" << errno;
		throw std::runtime_error(str.str());
	}

}

void Server::bind() const throw (std::runtime_error)
{
    struct sockaddr_in sin;
	
	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(m_ip.c_str());
	sin.sin_port = htons(m_port);

    if(::bind(m_socket,(struct sockaddr*)&sin,sizeof(sin)) < 0)
	{
		std::stringstream str;
        str << "Error in bind #" << errno;
		throw std::runtime_error(str.str());
	}
}

void Server::listen() const throw (std::runtime_error)
{
    if((::listen(m_socket, S_BACK_LOG_SIZE))<0)
	{
		std::stringstream str;
        str << "Error in listen #" << errno;
		throw std::runtime_error(str.str());
	}

    // if(-1 == (sock = SetNonBlocking(sock)))
	// {
	// 	perror("SetNonBlocking");
	// 	return -1;
	// }
    // CONSIDER USE THIS IN NEW FUNCTION
	std::cout << "listening..." << std::endl;
}

void Server::clientAccept() throw (std::runtime_error)
{
	int clientSocket;
	struct sockaddr_in sin;
	socklen_t sockLen = sizeof(sin);
	
	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(m_ip.c_str());
	sin.sin_port = htons(m_port);
	
	clientSocket = accept(m_socket, (struct sockaddr *)&sin, &sockLen);

	if(clientSocket > 0)
	{
		clientSocket = SetNonBlocking(clientSocket);
		if(clientSocket == -1)
		{
			std::stringstream str;
			str << "Error in SetNonBlocking #" << errno;
			throw std::runtime_error(str.str());
		}
		std::cout << clientSocket << " is connected\n";
		m_clients.insert(clientSocket);
	}
	
	else if(errno != EAGAIN && errno != EWOULDBLOCK)
	{
		std::stringstream str;
        str << "Error in clientAccept #" << errno;
		throw std::runtime_error(str.str());
	}

}

std::set<int> const& Server::clients() const
{
	return m_clients;
}

//TODO:: consider change Msg to some abstract class to keep the server/client abstraction

void Server::ServerStart() throw (std::runtime_error)
{
	
	getSocket();
	int optval = 1;
	SetSocketOptions(&optval, sizeof(optval));
	bind();
	listen();
	SetNonBlocking(m_socket);
	
}