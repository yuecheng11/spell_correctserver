#include "InetAddress.h"
InetAddress:: InetAddress()
{
	memset(&servaddr,0,sizeof(struct sockaddr_in));
}
InetAddress::InetAddress(unsigned short port)
{
	memset(&servaddr,0,sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = INADDR_ANY;
}
InetAddress::InetAddress(const char * ip,unsigned short port)
{
	memset(&servaddr,0,sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(ip);
}

InetAddress::InetAddress(const struct sockaddr_in & addr)
:servaddr(addr)
{
}

struct sockaddr_in* InetAddress::getInetAddressPtr()
{
	return &servaddr;
}

string InetAddress::getIp() const
{
	return string(inet_ntoa(servaddr.sin_addr));
}
unsigned short InetAddress::getPort() const
{
	return ntohs(servaddr.sin_port);
}