 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-18 11:06:13
 ///
 
#include "Thread.h"
#include <iostream>


namespace wd
{

Thread::Thread(ThreadCallback cb, Cache & cache)
: _pthId(0)
, _isRunning(false)
, _cb(cb)
, _cache(cache)
{
}


Thread::~Thread()
{
	if(_isRunning)
		pthread_detach(_pthId);
}

void Thread::start()
{
	pthread_create(&_pthId, 
				   NULL,
				   &Thread::threadFunc,
				   this);
	_isRunning = true;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthId, NULL);
}

void * Thread::threadFunc(void * arg)
{
	Thread * pThread = static_cast<Thread *>(arg);
	if(pThread)
		pThread->_cb(pThread->_cache);
}

}//end of namespace wd

