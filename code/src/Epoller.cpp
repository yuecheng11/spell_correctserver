#include "Epoller.h"

void Add_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd  =fd;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
	
}
void Del_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd  =fd;
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}
void Mod_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd  =fd;
	epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}

Epoller::Epoller(int fd)
	:epollfd(epoll_create(MAXEPOLLSIZE))
	,listenfd(fd)
	,_isloop(false)
{
	struct epoll_event events[MAXEPOLLSIZE];
	memset(events,0,sizeof(struct epoll_event));
	Add_event(epollfd,listenfd,EPOLLIN);
	
}

void Epoller::epoll_loop()
{
	if(!_isloop)
	{
		_isloop = true;

		/*while(1)
		{
			int conn_sock = _listenSock.socket_accept();
			if(conn_sock == -1)
			{
				perror("accept error");
				continue;
			}
			else
			{
				//init link
				Tcpconnection* pconn = new Tcpconnection(conn_sock);
				_connmap[conn_sock] = pconn;
				while(1)
				{
					cout<<"receive message: "<<pconn->receive().c_str()<<endl;
				}
					
			}
			}
			*/
		int ret;
		while(_isloop)
		{
			ret = epoll_wait(epollfd,events,MAXEPOLLSIZE,-1);
			//process msg
		}
	}
}
