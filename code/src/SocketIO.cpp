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
int SocketIO::writemessage(const char* str)
{
	int nwrite;
	nwrite = ::write(_fd,str,strlen(str));
	return nwrite;
}