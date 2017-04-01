#ifndef _THREAD_H_
#define _THREAD_H_
#include "Noncopyable.h"
#include <iostream>
#include <pthread.h>

class Thread:Noncopyable
{
public:
	Thread();
	~Thread();
	void start();
	void join();
private:
	virtual void run() = 0;
	static void *threadFunc(void*);
private:
	pthread_t _pthID;
	bool _isrunning;
};
#endif
