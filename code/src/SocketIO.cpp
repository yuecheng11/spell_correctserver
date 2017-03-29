#include "SocketIO.h"

SocketIO::SocketIO(int fd)
	:_fd(fd)
{

}
int SocketIO::readmessage()
{
	int nread;
	char* buf[1024];
	nread = ::read(_fd,buf,MAXSIZE);
	if(nread == -1)
	{
	}
	else if(nread == 0)
	{
	}
	else
	{
		cout<<"read message: "<<buf<<endl;
	}
}
int SocketIO::writemessage()
{
	int nwrite;
	nwrite = ::write(_fd,buf,MAXSIZE);
	if(nwrite == -1)
	{
	}
	else
	{
	}
}