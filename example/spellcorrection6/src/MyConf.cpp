#include "MyConf.h"
#include <iostream>
#include <fstream>
#include <utility>

MyConf::MyConf(const std::string &path) 
	: filepath_(path)
{
	init();
}

bool MyConf::init()
{
	std::ifstream ifs(filepath_.c_str());
	if(!ifs)
	{
		std::cout << "file read error" << std::endl;
		return false;
	}
	std::string line;
	while(getline(ifs, line))
	{
		std::istringstream iss(line);
		std::string key, value;
		iss >> key >> value;
		map_.insert(make_pair(key, value));
	}
	ifs.close();
	return true;
}

void MyConf::show()
{
	std::map<std::string, std::string>::const_iterator mit = map_.begin();
	for(; mit != map_.end(); ++mit)
	{
		std::cout << mit->first << " --> " << mit->second << std::endl;
	}
}
