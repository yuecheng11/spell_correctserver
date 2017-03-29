#include "Socket.h"

int create_sockfd()
{
	int fd = ::socket(AF_INET,SOCK_STREAM,0);
	if(fd == -1)
	{
		perror("create socket error!");
		exit(1);
	}
	return fd;
}
Socket::Socket()
:_listenfd(create_sockfd())
{
}
Socket::Socket(int fd)
:_listenfd(fd)
{
}
Socket::~Socket()
{
	::close(_listenfd);
}
Socket::socket_bind()
{

}