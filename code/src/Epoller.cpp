#include "Epoller.h"
#include <string.h>
#include "Socket.h"
#include <assert.h>

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

Epoller::Epoller(int fd,Buffer& buff)
	:epollfd(epoll_create(MAXEPOLLSIZE))
	,listenfd(fd)
	,listensock(listenfd)
	,_isloop(false)
	,_buff(buff)
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

		while(_isloop)
		{
			wait_Epollfd();
		}
	}
}
void Epoller::epoll_unloop()
{
	if(_isloop)
	{
		_isloop = false;
	}
}
void Epoller::wait_Epollfd()
{
	int ret;
	char buff[MAXSIZE];
	memset(buff,0,sizeof(buff));
	while(1)
	{
		ret = epoll_wait(epollfd,events,MAXEPOLLSIZE,-1);
		handle_events(ret,buff);
	}
}
void Epoller::handle_events(int num,char* buf)
{
	int fd;
	for(int i = 0;i<num; ++i)
	{
		fd = events[i].data.fd;
	    if((fd == listenfd) && (events[i].events & EPOLLIN))
	    {
	    	handle_accept();
	    }
		else if(events[i].events & EPOLLIN)
		{
			read_message(fd);
		}
		else if(events[i].events & EPOLLOUT)
		{
			write_message(fd);
		}
	}
}

void Epoller::handle_accept()
{
	int newcli = listensock.socket_accept();
	if(newcli == -1)
	{
		perror("accept error");
		return;
	}
	else
	{
		Add_event(epollfd,newcli,EPOLLIN);
		Tcpconnection* pconn = new Tcpconnection(newcli);
		_connmap[newcli] = pconn;
	}
}

void Epoller::read_message(int fd)
{
	map<int,Tcpconnection*>::iterator it 
		= _connmap.find(fd);
	assert(it != _connmap.end());
	string data;
	int ret = it->second->receive(data);
	if(ret == -1)
	{
		//perror("read error");
		//::close(fd);
		Del_event(epollfd,fd,EPOLLIN);
	}
	else if(ret == 0)
	{
		//fprintf(stderr,"clent error,close.\n");
		//::close(fd);
		Del_event(epollfd,fd,EPOLLIN);
	}
	else
	{
		Mod_event(epollfd,fd,EPOLLOUT);
		cout<<"Epoller: data: "<<data<<endl;
		int pos = data.find("\n");
		string subdata = data.substr(0,pos);
		Mytask task(subdata,fd);
		addTask(task);
	}
}

void Epoller::addTask(Task * ptask)
{
	_buff.push(ptask);
}

void Epoller::write_message(int fd)
{
	map<int,Tcpconnection*>::iterator it 
			= _connmap.find(fd);
	assert(it != _connmap.end());
	int ret = it->second->send("test\n");
	if(ret == -1)
	{
		//perror("read error");
		//::close(fd);
		Del_event(epollfd,fd,EPOLLOUT);
	}
	else
	{
		Mod_event(epollfd,fd,EPOLLIN);
	}
}
