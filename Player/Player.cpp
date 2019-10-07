#include "Player.h"
#include <sys/types.h>  
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */

Player::Player(std::string const& a_ip , int a_port)
:Client(a_ip, a_port)
,m_shipsAlive(0)
{

}

Player::~Player()
{

}
void Player::waitForMatch() throw (std::runtime_error)
{
    Msg matchMsg = {m_socket,-1 ,MATCH};
    Send(matchMsg);
    Receive();
}

void Player::printTable() const
{
    m_myTable.print();
}

void Player::buildTable()
{
    const int* sizes = SubMarinesTable::sizes();
    srand(time(0));
    const size_t tableSize = SubMarinesTable::size();
    while(m_shipsAlive<5)
    {
        size_t row = rand()%tableSize;
        size_t col = rand()%tableSize;
        SubMarinesTable::Direction dir = ((SubMarinesTable::Direction)(rand()%2));
        try
        {
            m_myTable.addSubmarine(std::make_pair(row,col), dir, SharedPtr<Submarine>(new Submarine(sizes[m_shipsAlive])));
            ++m_shipsAlive;
        }
        catch(std::runtime_error const& e)
        {
            std::cout << e.what() <<'\n';
        }
    }

}

size_t Player::Receive() throw (std::runtime_error)
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
		switch(buffer.m_msg_type)
        {
            case MATCH:
                buildTable();
                break;

            case TURN:
                std::cout << "HELLOOO" <<'\n';

            case COORDINATES:
            case WAS_HIT:
            case HIT_YES:
            case HIT_NO:
            case FINISHED:
            break;
        }
	}
	
	return 0;
}