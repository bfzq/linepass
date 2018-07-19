#pragma once
#ifndef __COMLINE__
#define __COMLINE__
#include <map>
#include <string>
#include <iostream>


class ComLine {
public:
	ComLine();
	~ComLine();
public:
	std::map<std::string, std::string>* map ;
	std::map<std::string, std::string>* getKeyValue(int argc,  char* argv[]);
	bool haveHelp() ;
	void printHelpInfo() ;
};

#endif // !__COMLINE__


