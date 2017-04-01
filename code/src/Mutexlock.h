#ifndef _MUTEXLOCK_H_
#define _MUTEXLOCK_H_
#include <pthread.h>
#include "Noncopyable.h"

class MutexLock:Noncopyable
{
public:
	MutexLock();
	~MutexLock();
	void lock();
	void unlock();
	pthread_mutex_t* getMutexLockPtr();
	
private:
	pthread_mutex_t _mutex;
	bool _isLock;
};


class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock& mutex)
	:mutexObj(mutex)
	{
		mutexObj.lock();
	}
	~MutexLockGuard()
	{
		mutexObj.unlock();
	}
private:
	MutexLock &mutexObj;
};

#endif
