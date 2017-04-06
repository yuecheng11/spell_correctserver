#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_
#include <iostream>
#include "Myconf.h"
#include "Socket.h"
#include "ThreadPoll.h"
#include <map>
#include "Tcpconnection.h"
#include "Epoller.h"
#include <string.h>

using namespace std;
class TcpServer
{
public:
	TcpServer(const char* ip,unsigned short port,Buffer& buff);
	void start();
	void stop();
	/*Threadpoll& getThreadpoll()
	{
		return _thredpoll;
	}*/
private:
	Socket _listenSock;
	map<int,Tcpconnection*> _connmap;
	Epoller _epoll;
	Buffer _buff;
};


#endif