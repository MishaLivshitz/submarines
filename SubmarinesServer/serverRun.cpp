#include "SubmarinesServer.h"

int main()
{
    SubmarinesServer s;

    s.ServerStart();
    s.ServerMatch();

    while(true)
    {
        s.clientAccept();
        const std::set<int> clients = s.clients();
        
        s.ServerReceive();
    }

}