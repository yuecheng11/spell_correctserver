#ifndef _BUFFER_H_
#define _BUFFER_H_
#include <iostream>
#include <queue>
#include "Mytask.h"
#include "Mutexlock.h"
#include "Condition.h"

class Buffer
{
public:
	Buffer(int size);
	~Buffer();
	void push(Task* ptask);
	Task* pop();

	bool full();
	bool empty();
	
private:
	int _size;
	queue<Task*> _tQue;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
};
#endif