#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "TcpServer.h"

using namespace std;

int main()
{
	SpellTcpserver server("../conf/my.conf");
	server.start();

	return 0;	
}