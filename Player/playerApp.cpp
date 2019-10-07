#include "Player.h"

int main()
{
    Player p;
    p.Connect();
    Msg msg = {0,1,MATCH, std::make_pair(5,5)};
    p.Send(msg);
    p.Receive();
    p.printTable();
}