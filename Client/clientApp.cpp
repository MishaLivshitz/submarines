#include "Client.h"
#include <iostream>
#include <cstring>
#include <utility>


int main()
{
    Client c;
    try
    {
        c.Connect();
        Msg msg = {1,2, TURN, std::make_pair(1,2)};
        c.Send(msg);
    }
    catch (std::runtime_error const& e)
    {
        std::cout << e.what() << std::endl;
    }

    while (true)
    {  
        c.Receive();
    }
    
    return 0;
}