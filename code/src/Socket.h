#ifndef _SOCKET_H_
#define _SOCKET_H_
#include "Noncopyable.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>			/* See NOTES */
#include <sys/socket.h>

class Socket:Noncopyable
{
public:
	Socket();
	Socket(int fd);
	~Socket();
	
	void ready();
private:
	void socket_bind();
	void socket_listen();
	int socket_accept();
	int fd();
private:
	int _listenfd;
};


#endif
