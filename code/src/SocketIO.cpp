#include "SocketIO.h"


SocketIO::SocketIO(int fd)
	:_fd(fd)
{

}

int SocketIO::getFd()
{
	return _fd;
}
int SocketIO::readmessage(char* buf,int size)
{

	
	return  ::read(_fd,buf,size);
	
}
int SocketIO::writemessage()
{
	int nwrite;
	char* buf[1024];
	nwrite = ::write(_fd,buf,MAXSIZE);
	if(nwrite == -1)
	{
	}
	else
	{
	}
	return nwrite;
}