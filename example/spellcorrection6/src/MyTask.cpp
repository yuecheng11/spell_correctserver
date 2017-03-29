 ///
 /// @file    MyTask.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-28 15:34:24
 ///

#include "MyTask.h"
#include "MyDict.h"
#include "Cache.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;


int tripleMin(const int & a, const int & b, const int & c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

MyTask::MyTask(const string & queryWord, int peerfd)
: _queryWord(queryWord)
, _peerfd(peerfd)
{
}

void MyTask::execute(Cache & cache)
{//每一个任务都是通过某一个线程来执行的，所以这里的cache
 //是由线程传过来的
#if 0
	cout << "Task::execute()--->query " << _queryWord << endl;
	MyDict * pDict = MyDict::createInstance();
	auto myDict = pDict->get_dict();
	cout << myDict[0].first << "-->" << myDict[0].second << endl;
#endif 
	string result = cache.query(_queryWord);
	if(result != string())
	{
		::write(_peerfd, result.c_str(), result.size());
		cout << "response client" << endl;
		return;
	}

	queryIndexTable();//查询索引表

	response(cache);//给客户端返回结果
}


void MyTask::queryIndexTable()
{
	auto indexTable = MyDict::createInstance()->get_index_table();
	string ch;

	for(int idx = 0; idx != _queryWord.size(); ++idx)
	{
		ch = _queryWord.substr(idx, 1);
		if(indexTable.count(ch))
		{
			cout << "indexTable has character " << ch << endl;
			statistic(indexTable[ch]);
		}
	}
}

void MyTask::response(Cache & cache)
{
	if(_resultQue.empty())
	{
		string result = "no answer!";
		int nwrite = ::write(_peerfd, result.c_str(), result.size());
		if(-1 == nwrite)
		{
			cout << "reponse error" << endl;
		}
	}
	else
	{
		MyResult result = _resultQue.top();
		int nwrite = ::write(_peerfd, result._word.c_str(), result._word.size());
		if(-1 == nwrite)
		{
			cout << "reponse error" << endl;
		}
		cache.addElement(_queryWord, result._word);//更新缓存
		cout << "respone(): add Cache" << endl;
	}
	cout << "reponse client" << endl;
}

void MyTask::statistic(set<int> & iset)
{
	auto dict = MyDict::createInstance()->get_dict();
	auto iter = iset.begin();
	for(; iter != iset.end(); ++iter)
	{
		string rhsWord = dict[*iter].first;
		int idist = distance(rhsWord);//进行最小编辑距离的计算
		if(idist < 3)
		{
			MyResult res;
			res._word = rhsWord;
			res._iFreq = dict[*iter].second;
			res._iDist = idist;
			_resultQue.push(res);
		}
	}
}

int MyTask::distance(const string & rhs)
{
	int lhsLen = _queryWord.size();
	int rhsLen = rhs.size();
	int editDist[lhsLen + 1][rhsLen + 1];
	
	for(int idx = 0; idx <= lhsLen; ++idx)
	{	editDist[idx][0] = idx;	}
	for(int idx = 0; idx <= rhsLen; ++idx)
	{	editDist[0][idx] = idx;	}
	
	string subLhs, subRhs;
	for(int i = 1; i <= lhsLen; ++i)
	{
		subLhs = _queryWord.substr(i-1, 1);
		for(int j = 1; j <= rhsLen; ++j)
		{
			subRhs = rhs.substr(j-1, 1);
			if(subLhs == subRhs)
			{
				editDist[i][j] = editDist[i - 1][j - 1];
			}
			else
			{
				editDist[i][j] = tripleMin(
					editDist[i][j - 1] + 1,
					editDist[i - 1][j] + 1,
					editDist[i - 1][j - 1] + 1);
			}
		}
	}
	return editDist[lhsLen][rhsLen];
}
