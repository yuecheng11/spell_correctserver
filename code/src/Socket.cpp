#include "Socket.h"
#include "InetAddress.h"

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
void Socket::socket_bind(InetAddress& addr)
{
	int ret = ::bind(_listenfd,
					(struct sockaddr*)(addr.getInetAddressPtr()),
						sizeof(struct sockaddr));
	if(ret == -1)
	{
		perror("bind error");
		exit(1);
	}
}
void Socket::socket_listen()
{
	int ret =  ::listen(_listenfd,10);
	if(ret == -1)
	{
		perror("listenfd error");
		exit(0);
	}
}

void Socket::ready(InetAddress& addr)
{
	setReuseAddr(true);
	setReusePort(true);
	socket_bind(addr);
	socket_listen();
}

int Socket::socket_accept()
{
	int peerfd;
	InetAddress peerAddr;
	socklen_t peerfdlen;
	peerfd = ::accept(_listenfd,
					(struct sockaddr*)(peerAddr.getInetAddressPtr()),
					&peerfdlen);
	if(peerfd == -1)
	{
		perror("accept error");
		return -1;
	}
	else
	{
		cout<<"accept a new client: "
			<<peerAddr.getIp()<<" port: "<<peerAddr.getPort()<<endl;
	}
	return peerfd;
}
void Socket::shutdownwrite()
{
	int ret = ::shutdown(_listenfd,SHUT_WR);
	if(ret == -1)
	{
		perror("shutdown error");
		exit(EXIT_FAILURE);
	}
}
int Socket::fd()
{
	return _listenfd;
}

void Socket::setReuseAddr(bool flag)
{
	int on = flag ? 1 : 0;
	int ret = ::setsockopt(_listenfd,
							SOL_SOCKET,
							SO_REUSEADDR,
							&on,
							static_cast<socklen_t>(sizeof(on)));

	if(ret == -1)
	{
		perror("setReuseAddr error");
		::close(_listenfd);
		exit(0);
		
	}
}

void Socket::setReusePort(bool flag)
{
#if SO_REUSEPORT
	int on = flag ? 1 : 0;
	int ret = ::setsockopt(_listenfd,
							SOL_SOCKET,
							SO_REUSEPORT,
							&on,
							static_cast<socklen_t>(sizeof(on)));

	if(ret == -1)
	{
		perror("setReusePort error");
		::close(_listenfd);
		exit(0);
		
	}
#else 
	if(flag)
	{
		cout<<"SO_REUSEPORT is not supported"<<endl;
	}
#endif
}