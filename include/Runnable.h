#ifndef RUNNABLE_H
#define RUNNABLE_H

namespace advcpp{


class Runnable
{

public:

    virtual ~Runnable() {};
    virtual void run() = 0;
};



} // advcpp

#endif