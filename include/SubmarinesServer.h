#ifndef SUBMARINES_SERVER_H
#define SUBMARINES_SERVER_H

#include "Server.h"
#include <map>
#include <WaitableQueue.h>
#include "Thread.h"
#include "SharedPtr.h"

class MatchesRunnable;

class SubmarinesServer: public Server
{
public:

    friend class MatchesRunnable;

    SubmarinesServer(std::string const& a_ip = "127.0.0.1" , int a_port = 8080);
    ~SubmarinesServer();


    void ServerMatch();
    virtual void ServerReceive() throw (std::runtime_error);
    virtual void ServerSend(int a_sock, Msg const& a_msg) throw (std::runtime_error);

private:

    std::map<int,int>           m_matches;
    advcpp::WaitableQueue<int>  m_ready;
    SharedPtr<advcpp::Thread>   m_matchesThread;

};




#endif