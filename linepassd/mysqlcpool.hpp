//
//  mysqlcpool.hpp
//  linepasswordindex
//
//  Created by Double on 2018/6/20.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef mysqlcpool_hpp
#define mysqlcpool_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "stdlib.h"
#include "mysqlc.h"


//#define MYSQLHOST

#define MYSQLPORT "mysql-port"
#define MYSQLHOST "mysql-host"
#define MYSQLUSER "mysql-user"
#define MYSQLPASSWD "mysql-passwd"
#define MYSQLDB "mysql-db"

struct mysql_item {
	bool status ; // true - using, false - not use
	MySQLC* mc ;
	mysql_item(MySQLC* m) {
		status = false ;
		mc = m ;
	}
	void setStatus(bool stat) {
		status = stat ;
	}
};

struct mysql_config {
	std::string host ;
	std::string user ;
	std::string passwd ;
	std::string db ;
	int port ;
	mysql_config(){}
	mysql_config(std::map<std::string, std::string>* m) {
		init(m) ;
	}
	void init(std::map<std::string, std::string>* m) {
		port = atoi((*m)[MYSQLPORT].c_str()) ;
		host = (*m)[MYSQLHOST] ;
		user = (*m)[MYSQLUSER] ;
		passwd = (*m)[MYSQLPASSWD] ;
		db = (*m)[MYSQLDB] ;
	}
};

class MysqlcPool {
private:
	struct mysql_item* pool ;
	uint16_t num ;
private:
	void uinit() ;
public:
	MysqlcPool() ;
	MysqlcPool(mysql_config, uint16_t) ;
	~MysqlcPool() ;
public:
	void init(mysql_config, uint16_t) ;
public:
	MySQLC* getMysqlCon() ;
	void backMysqlCon(MySQLC*) ;
};

#endif /* mysqlcpool_hpp */
