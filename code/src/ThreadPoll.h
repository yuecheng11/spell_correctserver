#ifndef _THREADPOLL_H_
#define _THREADPOLL_H_
#include <iostream>
#include <vector>
#include "Buffer.h"
#include "Thread.h"
#include "Mytask.h"
#include <string>

class Threadpoll
{
public:
	Threadpoll(int threadnum,Buffer& buff);
	~Threadpoll();
	void start();
	void stop();
	void addTask(Task* ptask);
	void threadFunc();
	
private:
	Task* getTask();
private:
	int _threadnum;
	vector<Thread *> vecThread;
	//int _buffsize;
	Buffer& _buff;
	bool _isExit;
};

#endif