#include "Tcpconnection.h"
#include <string>
#include <stdlib.h>

Tcpconnection::Tcpconnection(int fd)
	:_sockIO(fd)
	,_sock(fd)
	,_isShutdownWrite(false)
{
	
}
Tcpconnection::~Tcpconnection()
{
	
	if(!_isShutdownWrite)
	{
		shutdown();
	}
}
int Tcpconnection::receive()
{
	char buff[MAXSIZE];
	memset(buff,0,sizeof(buff));
	int nread = _sockIO.readmessage(buff,MAXSIZE);
	if(nread == -1)
	{
		perror("read error");
		::close(_sockIO.getFd());
	}
	else if(nread == 0)
	{
		cout<<"client close"<<endl;
		::close(_sockIO.getFd());
	}
	else 
	{
		cout<<"receive message: "<<buff<<endl;
		
	}

	return nread;
}

int Tcpconnection::send(const char* str)
{
	int nwrite = _sockIO.writemessage(str);
	if(nwrite == -1)
	{
		perror("read error");
		::close(_sockIO.getFd());
	}
	return nwrite;
}
void Tcpconnection::shutdown()
{
	if(!_isShutdownWrite)
	{
		_isShutdownWrite = true;
		_sock.shutdownwrite();
		
	}
}