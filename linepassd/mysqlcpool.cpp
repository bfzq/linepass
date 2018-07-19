//
//  mysqlcpool.cpp
//  linepasswordindex
//
//  Created by Double on 2018/6/20.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "mysqlcpool.hpp"

MysqlcPool::MysqlcPool() {}

MysqlcPool::MysqlcPool(mysql_config config, uint16_t num) {
	init(config, num) ;
}

MysqlcPool::~MysqlcPool() {
	uinit() ;
}

void MysqlcPool::init(mysql_config config, uint16_t num) {
	pool = (mysql_item*)malloc(sizeof(mysql_item) * num) ;
	this->num = num ;
	for (uint16_t i = 0; i < num; i++) {
		MySQLC* mc = new MySQLC() ;
		mc->connect(config.host, config.user, config.passwd, config.db, config.port) ;
		struct mysql_item mi(mc);
		pool[i] = mi ;
	}
}

void MysqlcPool::uinit() {
	free(pool) ;
}

MySQLC* MysqlcPool::getMysqlCon() {
	for (uint16_t i = 0; i < num; i++) {
		if (pool[i].status == false) {
			pool[i].status = true ;
			return pool[i].mc ;
		}
	}
	return nullptr ;
}


void MysqlcPool::backMysqlCon(MySQLC * mc) {
	for (uint16_t i = 0; i < num; i++) {
		if (pool[i].mc == mc) {
			pool[i].status = false ;
		}
	}
}
