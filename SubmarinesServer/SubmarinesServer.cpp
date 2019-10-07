#include "SubmarinesServer.h"
#include <cerrno>
#include <sstream>


class MatchesRunnable: public advcpp::Runnable
{
public:
    MatchesRunnable(SubmarinesServer& a_serv);
    ~MatchesRunnable() {};
    void run();

private:
    SubmarinesServer& m_serv;
};

MatchesRunnable::MatchesRunnable(SubmarinesServer& a_serv)
:m_serv(a_serv)
{

}

void MatchesRunnable::run()
{
    int socket1;
    int socket2;

    while(true)
    {
        m_serv.m_ready.dequeue(socket1);
        if(socket1 == -1) // Done flag
        {
            break;
        }

        m_serv.m_ready.dequeue(socket2);
        if(socket2 == -1) // Done flag
        {
            break;
        }

        m_serv.m_matches[socket1] = socket2;
        m_serv.m_matches[socket2] = socket1;
        
        Msg mMatch1 = {m_serv.m_socket,socket1,MATCH};
        Msg mMatch2 = {m_serv.m_socket,socket2,MATCH};
        Msg mTurn = {m_serv.m_socket,socket1,TURN};

        m_serv.ServerSend(socket1, mMatch1);
        m_serv.ServerSend(socket2, mMatch2);
        m_serv.ServerSend(socket1, mTurn);
    }
}

SubmarinesServer::SubmarinesServer(std::string const& a_ip, int a_port)
:Server(a_ip, a_port)
{
    
}

SubmarinesServer::~SubmarinesServer()
{

}

void SubmarinesServer::ServerReceive() throw (std::runtime_error)
{
    Msg buffer;
	int expectedDataLen = sizeof(buffer);
	int readBytes;
	std::set<int>::iterator itrB = m_clients.begin();
	std::set<int>::iterator itrE = m_clients.end();

	for (; itrE!=itrB; ++itrB)
	{
		readBytes = recv(*itrB, &buffer, expectedDataLen, 0);
		if(0 == readBytes)
		{ 	
			m_clients.erase(itrB);
			close(*itrB);
		} 			
		else if(readBytes > 0)		
		{ 			
			switch(buffer.m_msg_type)
        {
            case MATCH:
                m_ready.enqueue(*itrB);
                break;

            case TURN:

            case COORDINATES:
            case WAS_HIT:
            case HIT_YES:
            case HIT_NO:
            case FINISHED:
            break;
        }
		}
		else if(errno != EAGAIN && errno != EWOULDBLOCK) 		
		{ 			
			std::stringstream str;
        	str << "Error in ServerReceive #" << errno;
			throw std::runtime_error(str.str());		
		} 	
	}
}

void SubmarinesServer::ServerSend(int a_sock, Msg const& a_msg) throw (std::runtime_error)
{
    int sentBytes;

	sentBytes = send(a_sock, &a_msg, sizeof(a_msg), 0);
	if(0>sentBytes)
	{
		std::stringstream str;
		str << "Error in ServerSend #" << errno;
		throw std::runtime_error(str.str());
	}
}

void SubmarinesServer::ServerMatch()
{
    SharedPtr<advcpp::Runnable> r = SharedPtr<advcpp::Runnable> (new MatchesRunnable(*this));
    m_matchesThread = SharedPtr<advcpp::Thread>(new advcpp::Thread(*r));
    m_matchesThread->detach();

}