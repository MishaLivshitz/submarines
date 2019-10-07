#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <cstdio>

class UnCopyable
{
public:
    UnCopyable() {};

private:
    UnCopyable( UnCopyable const& _rhs);
    UnCopyable& operator=(UnCopyable const& _rhs);

};


inline int SetNonBlocking(int sock)
{
	int flags;
	
	if(-1== (flags = fcntl(sock,F_GETFL)))
	{
		perror("fcntl.F_GETFL");
		return -1;
	}
	
	if(-1== (fcntl(sock,F_SETFL, flags|O_NONBLOCK)))
	{
		perror("fcntl.F_SETFL");
		return -1;
	}
	
	return sock;
}


#endif
