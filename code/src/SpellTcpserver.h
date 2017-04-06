#ifndef _SPELLTCPSERVER_H_
#define _SPELLTCPSERVER_H_
#include <iostream>
class SpellTcpserver
{
public:
	SpellTcpserver(const string& fileStr,const int bufsize);
	~SpellTcpserver();
	void start();
	void stop();
private:
	Myconf _conf;
	int _buffsize;
	Buffer _buff;
	Threadpoll _threadpoll;
	TcpServer _tcpServer;
	//Buffer
};

#endif