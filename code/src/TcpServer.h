#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_
#include <iostream>
#include "Myconf.h"
#include "Socket.h"
#include <map>
#include "Tcpconnection.h"
#include <string.h>

using namespace std;
class TcpServer
{
public:
	TcpServer(const string& fileStr);
	void start();
	void stop();
private:
	Myconf _conf;
	Socket _listenSock;
	map<int,Tcpconnection*> _connmap;
	Epoller _epoll;
};


#endif