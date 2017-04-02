#include "Threadpollthread.h"
#include "ThreadPoll.h"
#include <iostream>

ThreadpollThread::ThreadpollThread(Threadpoll & threadpoll)
:_pThreadpoll(Threadpoll)
{
}

ThreadpollThread::run()
{
	_pThreadpoll.threadFunc();
}

