#ifndef _CONF_H
#define _CONF_H

#include <string>
#include <sstream>
#include <map>

///
///  配置文件类
///
class MyConf
{
public:
	MyConf(const std::string &);

	bool init();

	std::map<std::string, std::string> &getMap()
	{
		return map_;
	}

	void show();
private:
	std::string filepath_;
	std::map<std::string, std::string> map_;
};

#endif
