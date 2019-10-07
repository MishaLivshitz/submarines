#ifndef PLAYER_H
#define PLAYER_H

#include "Client.h"
#include "SubmarinesTable.h"
#include "OpponentTable.h"

class Player: public Client
{
    
public:
    Player(std::string const& a_ip = "127.0.0.1" , int a_port = 8080);
    ~Player();
    void waitForMatch() throw (std::runtime_error);
    size_t Receive() throw (std::runtime_error);

    void buildTable();
    void printTable() const;

private:
   // void buildTable();

private:

    SubMarinesTable m_myTable;
    OpponentTable   m_opponentTable;
    size_t          m_shipsAlive;
    
};



#endif