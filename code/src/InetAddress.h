#ifndef _INETADDRESS_H_
#define _INETADDRESS_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>
using namespace std;

class InetAddress
{
public:
	InetAddress();
	InetAddress(unsigned short port);
	InetAddress(const char* ip,unsigned short port);
	InetAddress(const struct sockaddr_in& addr);

	struct sockaddr_in* getInetAddressPtr();
	string getIp()const;
	unsigned short getPort() const;
	
private:
	struct sockaddr_in servaddr;
};


#endif
