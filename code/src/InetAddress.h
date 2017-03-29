#ifndef _INETADDRESS_H_
#define _INETADDRESS_H_
#include <netinet/in.h>
#include <string>
class InetAddress
{
public:
	InetAddress(unsigned short port);
	InetAddress(const char* ip,unsigned short port);
	InetAddress(struct sockaddr_in& addr);

	struct sockaddr_in* getInetAddressPtr();
	string getIp()const;
	unsigned short getPort() const;
	
private:
	struct sockaddr_in servaddr
};


#endif