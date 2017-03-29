 ///
 /// @file    Threadpool.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-19 10:18:25
 ///
 
#ifndef _MY_THREADPOOL_H_
#define _MY_THREADPOOL_H_
#include "Buffer.h"
#include "Cache.h"
#include "MyConf.h"
#include <vector>
#include <functional>

using std::vector;

namespace wd 
{
class Thread;
class Threadpool
{
public:
	typedef std::function<void(Cache &)> Task;
	Threadpool(int threadNum, int bufSize, MyConf & conf);
	~Threadpool();

	void start();
	void stop();

	void addTask(Task ptask);

	void threadFunc(Cache & cache);

	void readCache();
	void updateCache();//更新缓存的策略

private:
	Task getTask();
	
private:
	int _threadNum;
	vector<Thread *> _vecThreads;
	int _bufSize;
	Buffer _buf;
	bool _isExit;
	Cache _cache;
	MyConf & _conf;
};

}//end of namespace wd

#endif
