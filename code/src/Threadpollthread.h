#ifndef _THREADPOLLTHREAD_H_
#define _THREADPOLLTHREAD_H_
#include "thread.h"

class ThreadpollThread:Thread
{
public:
	ThreadpollThread(Threadpoll & threadpoll);
	void run();
private:
	Threadpoll& _pThreadpoll;
};

#endif