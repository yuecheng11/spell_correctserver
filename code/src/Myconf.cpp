#include "Myconf.h"

Myconf::Myconf(const string & filepath)
:_filepath(filepath)
{
	initmap();
}

void Myconf::initmap()
{
	ifstream in(_filepath.c_str());
	//cout<<"file path: "<<_filepath.c_str()<<endl;
	if(!in)
	{
		cout<<"file read error"<<endl;
		return ;
	}
	string line;
	while(getline(in,line))
	{
		istringstream iss(line);
		string key,value;
		iss>>key>>value;
		_confmap.insert(make_pair(key,value));
	}
	in.close();
}

void Myconf::show()
{
	map<string,string>::iterator iter = _confmap.begin();
	for(;iter != _confmap.end();++iter)
	{
		cout<<iter->first<<" : "<<iter->second<<endl;
	}
	
}