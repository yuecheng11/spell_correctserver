 ///
 /// @file    Cache.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-31 08:52:49
 ///
 
#include "Cache.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

Cache::Cache(int num)
: _hashMap(num)
{}

Cache::Cache(const Cache & rhs)
: _hashMap(rhs._hashMap)
{}


void Cache::addElement(const string & key, const string & value)
{
	_hashMap[key] = value;	
}

string Cache::query(const string & word)
{
	auto iter = _hashMap.find(word);
	if(iter != _hashMap.end())
	{
		return iter->second;
	}
	else
	{
		return string();
	}
}

void Cache::readFromFile(const string & filename)
{
	ifstream ifs(filename.c_str());
	if(!ifs.good())
	{
		cout << "open cache file error!" << endl;
		return;
	}

	string key, value;
	while(ifs >> key >> value)
	{
		_hashMap.insert(std::make_pair(key, value));
		cout << key << " " << value << endl;
	}
}

void Cache::writeToFile(const string & filename)
{
	ofstream ofs(filename.c_str());
	if(!ofs.good())
	{
		cout << "ofstream:write cache file error" << endl;
		return ;
	}

	auto iter = _hashMap.begin();
	for(; iter != _hashMap.end(); ++iter)
	{
		ofs << iter->first << "\t" << iter->second << endl;
	}
}

void Cache::update(const Cache & rhs)
{
	auto iter = rhs._hashMap.begin();
	for(; iter != rhs._hashMap.end(); ++iter)
	{
		_hashMap.insert(*iter);
	}
}
