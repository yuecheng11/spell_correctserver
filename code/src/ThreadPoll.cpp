#include "Threadpoll.h"
#include <unistd.h>
using namespace std;

Threadpoll::Threadpoll(int threadnum,int bufsize)
:_threadnum(threadnum)
,_buffsize(bufsize)
,_buff(_buffsize)
,_isExit(false)
{
	vecThread.reserve(_thnum);
}

Threadpoll::~Threadpoll()
{
	if(!_isExit)
	{
		stop();
	}
}
void Threadpoll::start()
{
	for(int idx = 0;idx != _threadnum;++idx)
	{
		Thread* pThread = new ThreadpollThread(*this);
		vecThread.pushback(pThread);
	}
	vector<Thread *>::iterator it = vecThread.begin();
	for(;it != vecThread.end();++it)
	{
		(*it)->start();
	}
}

void Threadpoll::stop()
{
	if(!_isExit)
	{
		while(!_buff.empty())
		{
			sleep(1);
		}
		
		_isExit = true;
		vector<Thread *>::iterator it = vecThread.begin();
		for(;it != vecThread.end();++it)
		{
			(*it)->join();
			delete (*it);
		}

		vecThread.clear();
	}
}

void Threadpoll::addTask(Task * ptask)
{
	_buff.push(ptask);
}

Task* Threadpoll::getTask()
{
	return _buff.pop();
}

void Threadpoll::threadFunc()
{
	while(!_isExit)
	{
		Task* pTask = getTask();
		if(NULL != pTask)
		{
			pTask->process();
		}
	}
}