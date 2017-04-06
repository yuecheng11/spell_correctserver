#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "TcpServer.h"
#include "SpellTcpserver.h"

using namespace std;

int main()
{
	SpellTcpserver server("../conf/my.conf",1000);
	server.start();

	return 0;	
}