#ifndef _SPELLTCPSERVER_H_
#define _SPELLTCPSERVER_H_
#include <iostream>
class SpellTcpserver
{
public:
	SpellTcpserver(const string& fileStr);
	~SpellTcpserver();
	void start();
	void stop();
private:
	Myconf _conf;
	TcpServer _tcpServer;
	Threadpoll _threadpoll;
};

#endif