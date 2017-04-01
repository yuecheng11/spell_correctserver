#include "Mutexlock.h"

MutexLock::MutexLock()
:_isLock(false)
{
	pthread_mutex_init(&_mutex,NULL);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destory(&_mutex);
}

void MutexLock::lock()
{
	if(!_isLock)
	{
		pthread_mutex_lock(&_mutex);
		_isLock = true;
	}
}
void MutexLock::unlock()
{
	if(_isLock)
	{
		pthread_mutex_unlock(&_mutex);
		_isLock = false;
	}
}

pthread_mutex_t* MutexLock::getMutexLockPtr()
{
	return &_mutex;
}
