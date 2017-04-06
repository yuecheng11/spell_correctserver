#ifndef _EPOLLER_H_
#define _EPOLLER_H_
#include <iostream>
#include <sys/epoll.h>
#include "Socket.h"
#include "Tcpconnection.h"
#include <map>
#include <stdio.h>
#include "Mytask.h"
#include "Buffer.h"
#include <string>

using namespace std;
#define MAXEPOLLSIZE 1000
class Epoller
{
public:
	Epoller(int fd,Buffer& buff);
	void epoll_loop();
	void wait_Epollfd();
	void handle_events(int ret,char* buf);
	void handle_accept();
	void read_message(int fd);
	void write_message(int fd);
	void epoll_unloop();
	
	void addTask(Task * ptask);
private:

private:
	int epollfd;
	int listenfd;
	Socket listensock;
	bool _isloop;
	struct epoll_event events[MAXEPOLLSIZE];
	map<int,Tcpconnection*> _connmap;

	Buffer& _buff;
};

#endif