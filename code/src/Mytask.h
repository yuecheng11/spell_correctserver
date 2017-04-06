#ifndef _MYTASK_H
#define _MYTASK_H
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

class Task
{
public:
	virtual void process() = 0;
};

class Mytask:public Task
{
public:
	Mytask(string data,int fd)
	:queryWord(data)
	,connfd(fd)
	{
		sendstr = "0";
	}
	int process(string& str)
	{
		sendstr = queryWord;
		int ret = ::write(connfd,sendstr.c_str(),1);
		if(ret > 0)
			cout<<"response cliend"<<endl;
		return connfd;
	}
private:
	string queryWord;
	string sendstr;
	int connfd;	
};
#endif