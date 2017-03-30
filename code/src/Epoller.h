#ifndef _EPOLLER_H_
#define _EPOLLER_H_
#include <iostream>
#include <sys/epoll.h>
#include "Socket.h"
using namespace std;
#define MAXEPOLLSIZE 1000
class Epoller
{
public:
	Epoller(int fd);
	void epoll_loop();
private:

private:
	int epollfd;
	int listenfd;
	bool _isloop;
	struct epoll_event events[MAXEPOLLSIZE];
};

#endif