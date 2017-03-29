 ///
 /// @file    test_server.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-25 22:03:48
 ///
 
#include "SpellcorrectServer.h"
#include <iostream>



int main(void)
{
	wd::SpellcorrectServer server("./conf/my.conf");
	server.start();

	return 0;
}
