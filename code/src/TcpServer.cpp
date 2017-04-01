#include "TcpServer.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include <sstream>
#include "Tcpconnection.h"



TcpServer::TcpServer(const char* ip,unsigned short port)
:_listenSock()
,_epoll(_listenSock.fd())
{
	
	InetAddress Inetaddr(mapconf["my_ip"].c_str(),port);
	_listenSock.ready(Inetaddr);
	cout<<"listen socket init succed,wait new connect:"<<endl;
}
void TcpServer::start()
{

	_epoll.epoll_loop();
	
}

void TcpServer::stop()
{
	_epoll.epoll_unloop();
}