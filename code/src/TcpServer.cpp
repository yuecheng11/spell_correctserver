#include "TcpServer.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include <sstream>
#include "Tcpconnection.h"

unsigned short strtoshort(string port)
{
	stringstream ss;
	ss<<port;
	unsigned short newport;
	ss>>newport;

	cout<<"add test new port: "<<newport<<endl;
	return newport;
}

TcpServer::TcpServer(const string& fileStr)
	:_conf(fileStr)
	,_listenSock()
	,_epoll(_listenSock.fd())
{
#if 1 
	// test show configure
	_conf.show();
#endif

	map<string,string> mapconf = _conf.getConfMap();
	unsigned short port = strtoshort(mapconf["my_port"]);
	
	InetAddress Inetaddr(mapconf["my_ip"].c_str(),port);
	_listenSock.ready(Inetaddr);
	cout<<"listen socket init succed,wait new connect:"<<endl;
}
void TcpServer::start()
{

	_epoll.epoll_loop();
	
}