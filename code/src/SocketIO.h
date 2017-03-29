#ifndef _SOCKETIO_H_
#define _SOCKETIO_H_
#include "Socket.h"
#define MAXSIZE 1024

class SocketIO
{
public:
	SocketIO(int fd);

	int readmessage();
	int writemessage();
private:
	int _fd;
};


#endif