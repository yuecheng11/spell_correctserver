#include "SpellTcpserver.h"

unsigned short strtoshort(string port)
{
	stringstream ss;
	ss<<port;
	unsigned short newport;
	ss>>newport;

	cout<<"add test new port: "<<newport<<endl;
	return newport;
}

SpellTcpserver::SpellTcpserver(const string & fileStr,const int bufsize)
:_conf(fileStr)
,_buff(bufsize)
,_threadpoll(4,_buff)
,_tcpServer(_conf.getConfMap()["my_ip"].c_str(),strtoshort(_conf.getConfMap()["my_port"]),_buff)

{
	#if 1 
	// test show configure
	_conf.show();
	#endif

}

void SpellTcpserver::start()
{
	_tcpServer.start();
	_threadpoll.start();
}

void SpellTcpserver::stop()
{
	_tcpServer.stop();
	Threadpoll.stop();
}