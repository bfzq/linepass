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
#include "threadpool.h"


//#define MYSQLHOST

#define MYSQLPORT "mysql-port"
#define MYSQLHOST "mysql-host"
#define MYSQLUSER "mysql-user"
#define MYSQLPASSWD "mysql-passwd"
#define MYSQLDB "mysql-db"
#define MYSQLBEATTIME "mysql-beat-time"

struct mysql_item {
  bool status; // true - using, false - not use
  Mysqlc* mc;
  mysql_item(Mysqlc* m) {
    status = false;
    mc = m;
  }
    
    //mysql_item& operator=(const mysql_item& mi) {
    //    status = mi.status;
    //    mc = mi.mc;
    //    return *this;
    //}
    
  void setStatus(bool stat) {
    status = stat;
  }
};

struct mysql_config {
  std::string host;
  std::string user;
  std::string passwd;
  std::string db;
  int port;
    unsigned int heart_time;
  mysql_config() = default;
  mysql_config(std::map<std::string, std::string>* m) {
    init(m);
  }
  void init(std::map<std::string, std::string>* m) {
    port = atoi((*m)[MYSQLPORT].c_str());
    host = (*m)[MYSQLHOST];
    user = (*m)[MYSQLUSER];
    passwd = (*m)[MYSQLPASSWD];
    db = (*m)[MYSQLDB];
        heart_time = atoi((*m)[MYSQLBEATTIME].c_str());
  }
};

class MysqlcPool {
private:
    fivestar::ThreadPool thread;
  std::vector<mysql_item> pool;
    unsigned int _heart_time = 3;
private:
  void uinit();
    /*the heart beat of connections*/
    void keepAlive();
public:

  MysqlcPool() = default;
  /* arg1 is mysql info, arg2 is num of mysql connections */
  MysqlcPool(mysql_config, uint16_t);
  ~MysqlcPool();
public:
  void init(mysql_config, uint16_t);
public:
  Mysqlc* getMysqlCon();
  void backMysqlCon(Mysqlc*);
};

#endif /* mysqlcpool_hpp */
