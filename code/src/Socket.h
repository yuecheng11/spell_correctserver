#ifndef _SOCKET_H_
#define _SOCKET_H_
#include "Noncopyable.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>			/* See NOTES */
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

using namespace std;

class InetAddress;
class Socket:Noncopyable
{
public:
	Socket();
	Socket(int fd);
	~Socket();
	
	void ready(InetAddress& addr);
	int socket_accept();
	void shutdownwrite();
	int fd();
private:
	void socket_bind(InetAddress& addr);
	void socket_listen();
	
	void setReuseAddr(bool flag);
	void setReusePort(bool flag);
private:
	int _listenfd;
};


#endif
