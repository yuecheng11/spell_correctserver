#ifndef _MYCONF_H_
#define _MYCONF_H_
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;

class Myconf
{
public:
	Myconf(const string& filepath);
	void initmap();
	void show();
	map<string,string>& getConfMap()
	{
		return _confmap;
	}
private:
	string _filepath;
	map<string,string> _confmap; 
};

#endif