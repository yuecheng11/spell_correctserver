#ifndef _SOCKETIO_H_
#define _SOCKETIO_H_
#include "Socket.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>			/* See NOTES */
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

using namespace std;


#define MAXSIZE 1024

class SocketIO
{
public:
	SocketIO(int fd);

	int getFd();
	int readmessage(char* buf,int size);
	int writemessage();
private:
	int _fd;
};


#endif