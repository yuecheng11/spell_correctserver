 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-18 11:06:13
 ///
 
#ifndef _MY_THTREAD_H_
#define _MY_THTREAD_H_

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

class Thread : wd::Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback cb);
	~Thread();

	void start();
	void join();

	static void * threadFunc(void *);
private:
	pthread_t _pthId;
	bool _isRunning;
	ThreadCallback _cb;
};


#endif

