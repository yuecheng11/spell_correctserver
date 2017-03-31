#ifndef _MYTASK_H
#define _MYTASK_H
#include<iostream>
class Task
{
public:
	virtual void process() = 0;
};

class Mytask:public Task
{
public:
	void process()
	{
		cout<<"todo"<<endl;
	}
};
#endif