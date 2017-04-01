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

SpellTcpserver::SpellTcpserver(const string & fileStr)
:_conf(fileStr)
,_tcpServer(_conf.getConfMap()["my_ip"].c_str(),strtoshort(_conf.getConfMap()["my_port"]))
,Threadpoll(4,100)
{
	#if 1 
	// test show configure
	_conf.show();
	#endif

}
void SpellTcpserver::stop()
{
	_tcpServer.stop();
	Threadpoll.stop();
}