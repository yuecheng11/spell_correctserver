#include "Thread.h"

Thread::Thread()
:_pthID(0)
,_isrunning(false)
{
}

Thread::~Thread()
{
	if(_isrunning)
	{
		pthread_detach(_pthID);
	}
}

void Thread::start()
{
	pthread_create(&_pthID,
					NULL,
					&Thread::threadFunc,
					this);
	_isrunning = true;
}

void Thread::join()
{
	if(_isrunning)
	{
		pthread_join(_pthID,NULL);
	}
}
void Thread::threadFunc(void *arg)
{
	Thread* pthread = static_cast<Thread *>(arg);
	if(pthread)
	{
		pthread->run();
	}
}
