 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-19 10:23:27
 ///
 
#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{
Threadpool::Threadpool(int threadNum, int buffSize, MyConf & conf)
: _threadNum(threadNum)
, _bufSize(buffSize)
, _buf(_bufSize)
, _isExit(false)
, _conf(conf)
{
	_vecThreads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
	if(!_isExit)
	{
		stop();
	}
}

void Threadpool::start()
{
	readCache();//先从文件里面读cache

	for(int idx = 0; idx != _threadNum; ++idx)
	{
		Thread * pThread = new Thread(
				std::bind(&Threadpool::threadFunc, this, std::placeholders::_1),
				_cache);//将线程池里面的cache复制给每一个线程
		_vecThreads.push_back(pThread);
	}
	vector<Thread *>::iterator it = _vecThreads.begin();
	for(; it != _vecThreads.end(); ++it)
	{
		(*it)->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit)
	{
		while(!_buf.empty())
		{
			sleep(1);
		}
		_isExit = true;
		vector<Thread *>::iterator it;
		for(it = _vecThreads.begin();
			it != _vecThreads.end();
			++it)
		{
			(*it)->join();
			delete (*it);
		}
		_vecThreads.clear();
	}
}

void Threadpool::addTask(Task ptask)
{
	_buf.push(ptask);
}

Threadpool::Task Threadpool::getTask()
{
	return _buf.pop();
}


void Threadpool::threadFunc(Cache & cache)
{
	while(!_isExit)
	{
		Task ptask = getTask();
		if(ptask)
			ptask(cache);
	}
}

void Threadpool::readCache()
{
	_cache.readFromFile(_conf.getMap()["my_cache"]);
}


void Threadpool::updateCache()
{
	cout << "timer executing, update Caches" << endl;
	for(int idx = 0; idx != _threadNum; ++idx)
	{//先把每个线程的cache写回到线程池的cache
		_cache.update(_vecThreads[idx]->getCache());
	}
	for(int idx = 0; idx != _threadNum; ++idx)
	{//再把整个大cache再写回到每个线程
		_vecThreads[idx]->getCache().update(_cache);
	}

	//最后把整个大cache保存到文件里面
	_cache.writeToFile(_conf.getMap()["my_cache"]);
}

}// end of namespace wd


