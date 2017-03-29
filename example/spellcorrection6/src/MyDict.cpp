#include "MyDict.h"
#include <iostream>
#include <fstream>
#include <sstream>

MyDict *MyDict::pInstance = NULL;

MyDict* MyDict::createInstance()
{
	if(NULL == pInstance)
	{
		pInstance = new MyDict;
	}
	return pInstance;
}

std::vector<std::pair<std::string, int> > & MyDict::get_dict()
{
	return dict_;
}

std::map<std::string, std::set<int> > &MyDict::get_index_table()
{
	return index_table_;
}

void MyDict::show_dict()
{
	auto iter = dict_.begin();
	for(; iter != dict_.end(); ++iter)
	{
		std::cout << iter->first << "-->"
				  << iter->second << std::endl;
	}
}

void MyDict::show_index_table()
{
	auto iter = index_table_.begin();
	for(; iter != index_table_.end(); ++iter)
	{
		std::cout << iter->first << "-->";
		auto sit = iter->second.begin();
		for(; sit != iter->second.end(); ++sit)
		{
			std::cout << *sit << " ";
		}
		std::cout << std::endl;
	}
}

void MyDict::read_from(const char * dictpath)
{
	std::ifstream in(dictpath);	
	if(!in)
	{
		std::cout << __DATE__ << " " << __TIME__
				  << __FILE__ << " " << __LINE__
	              << ": dict read error" << std::endl;
		exit(-1);
	}
	
	std::string line;
	while(getline(in, line))
	{
		std::stringstream ss(line);
		std::string key;
		int value;
		ss >> key >> value;
		dict_.push_back(make_pair(key, value));
	}
	in.close();
}
//private:
MyDict::MyDict()
{}


void MyDict::init(const char *dictpath)
{
	read_from(dictpath);
	//read_from(dictpath2);
	//创建索引表
	for(size_t idx = 0; idx != dict_.size(); ++idx)
	{
		record_to_index(idx);
	}
}

void MyDict::record_to_index(int idx)
{
	std::string key;
	std::string word = dict_[idx].first;
	for(std::size_t iidx = 0; iidx != word.size(); ++iidx)
	{
		char ch = word[iidx];
		if(ch & (1 << 7))
		{//存储utf-8编码的中文字符
			if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)
			{
				key = word.substr(iidx, 2);
				++iidx;
			}
			else if((ch & 0xF0) == 0xE0)
			{
				key = word.substr(iidx, 3);
				iidx += 2;
			}
			else if((ch & 0xF0) == 0xF0)
			{
				key = word.substr(iidx, 4);
				iidx += 3;
			}
			else if((ch & 0xFF) == 0xF8)
			{
				key = word.substr(iidx, 5);
				iidx += 4;
			}
			else if((ch & 0xFF) == 0xFE)
			{
				key = word.substr(iidx, 6);
				iidx += 5;
			}
		}
		else
		{
			key = word.substr(iidx, 1);
		}
		index_table_[key].insert(idx);
	}
}
