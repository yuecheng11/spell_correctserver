 ///
 /// @file    SpellcorrectServer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-25 21:29:32
 ///
 
#include "SpellcorrectServer.h"
#include "MyDict.h"
#include "MyTask.h"

#include <iostream>
#include <sstream>
#include <functional>

using std::cout;
using std::endl;

unsigned short str2unshort(const string & str)
{
	unsigned short port;
	std::stringstream ss;
	ss << str;
	ss >> port;
	return port;
}

namespace wd
{

SpellcorrectServer::SpellcorrectServer(const string & cfgFileName)
: _conf(cfgFileName)
, _tcpServer(_conf.getMap()["my_ip"].c_str(), 
		str2unshort(_conf.getMap()["my_port"]))
, _threadpool(4,1000,_conf)
, _timer(std::bind(&Threadpool::updateCache, &_threadpool), 3, 10)
{
	MyDict * pMyDict = MyDict::createInstance();
	pMyDict->init(_conf.getMap()["my_dict"].c_str());
}


void SpellcorrectServer::start()
{
	_threadpool.start();
	_timer.start();

	using namespace std::placeholders;
	_tcpServer.setConnectionCallback(
			std::bind(&SpellcorrectServer::onConnection, this, _1));
	_tcpServer.setMessageCallback(
			std::bind(&SpellcorrectServer::onMessage, this, _1));
	_tcpServer.setCloseCallback(
			std::bind(&SpellcorrectServer::onClose, this, _1));

	_tcpServer.start();
}

void SpellcorrectServer::onConnection(TcpConnectionPtr conn)
{
	cout << conn->toString() << "has connected!" << endl;
	conn->send("welcome to SpellCorrect Server!");
}

void SpellcorrectServer::onMessage(TcpConnectionPtr conn)
{
	string msg = conn->receive();
	cout << msg << endl;
	//conn->send(msg);
	
	int pos = msg.find('\n');
	string data = msg.substr(0, pos);
	cout << data << endl;
	cout << "data's size = " << data.size() << endl;
	MyTask task(data, conn->fd());
	_threadpool.addTask(std::bind(&MyTask::execute, task, std::placeholders::_1));
}

void SpellcorrectServer::onClose(TcpConnectionPtr conn)
{
	cout << conn->toString() << " has closed!" << endl;
}

}// end of namespace wd
