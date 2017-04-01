#ifndef _CONDITION_H_
#define _CONDITION_H_
#include "Noncopyable.h"
#include "Mutexlock.h"
#include <pthread.h>

class MutexLock;

class Condition
{
public:
	Condition(MutexLock& mutex);
	~Condition();
	void wait();
	void notify();
	void notifyAll();
private:
	pthread_cond_t _cond;
	MutexLock& _mutex;
};

#endif