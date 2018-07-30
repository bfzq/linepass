#pragma once
#ifndef __MYSQLC__
#define __MYSQLC__

#include "mysql.h"
#include <string>
#include <vector>
#include <iostream>
#include <functional>

#define _mysql_library_init mysql_library_init(0, NULL, NULL)
#define _mysql_library_end mysql_library_end()

class MySQLC {
public:
	MySQLC();
	~MySQLC();
private:
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
public:
	bool connect(std::string host, std::string user, std::string password, std::string db, int port);
	void disConnect();
	bool query(std::string sql, std::function<bool(MYSQL_ROW)> f, std::function<void(void)> empty);
	std::vector<std::string> getValue(std::string column);
	bool query(std::string sql) ;
};

#endif // !__MYSQLC__
