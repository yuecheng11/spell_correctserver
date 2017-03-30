#ifndef _TCPCONNECTION_H_
#define _TCPCONNECTION_H_
#include <iostream>
#include "Noncopyable.h"
#include <string>
#include "SocketIO.h"

using namespace std;

class Tcpconnection:Noncopyable
{
public:
	Tcpconnection(int fd);
	~Tcpconnection();
	string receive();
	void send();
	void shutdown();
private:
	Socket _sock;
	SocketIO _sockIO;
	bool _isShutdownWrite;
	//Socket _fd;
};

#endif