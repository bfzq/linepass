//
//  mysqlcpool.cpp
//  linepasswordindex
//
//  Created by Double on 2018/6/20.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "mysqlcpool.hpp"
//#include <thread>

// MysqlcPool::MysqlcPool() {}

MysqlcPool::MysqlcPool(mysql_config config, uint16_t num) {
	init(config, num) ;
}

MysqlcPool::~MysqlcPool() {
	uinit() ;
}

void MysqlcPool::init(mysql_config config, uint16_t num) {
	pool = (mysql_item**)malloc(sizeof(mysql_item*) * num) ;
	this->num = num ;
    _heart_time = config.heart_time ;
    
    thread.setMaxQueueSize(3) ;
    thread.start(1) ;
    
	for (uint16_t i = 0; i < num; i++) {
		Mysqlc* mc = new Mysqlc() ;
		mc->connect(config.host.c_str(), config.user.c_str(), config.passwd.c_str(), config.db.c_str(), config.port) ;
		mc->setCharacterSet("utf8mb4") ;
		struct mysql_item* mi = new mysql_item(mc);
		pool[i] = mi ;
	}
//    printf("%p,%p\n",pool,pool[0]->mc) ;
    keepAlive() ;
}

void MysqlcPool::uinit() {
    for (int i = 0; i < num; i++) {
        free(pool[i]) ;
    }
	free(pool) ;
    pool = nullptr ;
}

void MysqlcPool::keepAlive() {
    thread.run([this](){
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(_heart_time)) ;
            for(unsigned int i = 0; i < num; i++) {
                mysql_item* mi = pool[i] ;
                if (mi->status == false) {
                    Mysqlc* mc = pool[i]->mc ;
                    if (!mc->alive()) mc->reConnect() ;
                }
            }
        }
    }) ;
}

Mysqlc* MysqlcPool::getMysqlCon() {
	for (uint16_t i = 0; i < num; i++) {
		if (pool[i]->status == false) {
			pool[i]->status = true ;
			return pool[i]->mc ;
		}
	}
	return nullptr ;
}


void MysqlcPool::backMysqlCon(Mysqlc * mc) {
	for (uint16_t i = 0; i < num; i++) {
		if (pool[i]->mc == mc) {
			pool[i]->status = false ;
		}
	}
}
