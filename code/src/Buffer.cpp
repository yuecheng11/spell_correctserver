#include "Buffer.h"

Buffer::Buffer(int size)
:_size(size)
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
{

}

Buffer::~Buffer()
{
	
}

void Buffer::push(Task * ptask)
{
	MutexLockGuard mlg(_mutex);
	while(full())
	{
		_notFull.wait();
	}
	_tQue.push(ptask);
	_notEmpty.notify();
}
Task* Buffer::pop()
{
	MutexLockGuard mlg(_mutex);
	while(empty())
	{
		_notEmpty.wait();
	}
	Task* ptask = _tQue.front();
	_tQue.pop();
	_endQue.push(ptask);
	_notFull.notify();
}

bool Buffer::full()
{
	return _size == _tQue.size();
}

bool Buffer::empty()
{
	return 0 == _tQue.size();
}