 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-18 11:06:13
 ///
 
#ifndef __MY_THREAD_H_
#define __MY_THREAD_H_

#include "Noncopyable.h"
#include "Cache.h"
#include <pthread.h>
#include <functional>


namespace wd
{

class Thread : Noncopyable
{
public:
	typedef std::function<void(Cache &)> ThreadCallback;
	Thread(ThreadCallback cb, Cache & cache);
	~Thread();

	void start();
	void join();

	::Cache & getCache()
	{	return _cache;	}

	static void * threadFunc(void * arg);

private:
	pthread_t _pthId;
	bool _isRunning;
	ThreadCallback _cb;
	Cache _cache;
};

}//end of namespace wd

#endif
