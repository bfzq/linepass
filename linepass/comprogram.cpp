//
//  comprogram.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "comprogram.hpp"

client_config::client_config(std::map<std::string, std::string>* m) {
	init(m) ;
}

void client_config::init(std::map<std::string, std::string> * m) {
	connect_host = (*m)[CONNECTHOST] ;
	connect_port = atoi((*m)[CONNECTPORT].c_str()) ;
	connect_user = (*m)[CONNECTUSER] ;
	connect_password = (*m)[CONNECTPASSWORD] ;
}

ComProgram::ComProgram() {
	link = new LineLink(LineLink::CLIENT) ;
	cmd = new Command() ;
	ls = new LineSecret() ;
//	lc = new ComLine() ;
}

ComProgram::~ComProgram() {
	delete link ;
	delete cmd ;
	delete ls ;
	ls = nullptr ;
	cmd = nullptr ;
	link = nullptr ;
}


bool ComProgram::connectServer() {
	/*
	 *	设置连接端口和ip
	 */
	link->clientPort(cc.connect_port) ;
	link->clientHost(cc.connect_host) ;
	
	
	if(!link->init()) return false;
	return link->clientConnect() ;
}


bool ComProgram::interactive() {
	struct proto_msg pm ;
	while (cmd->input()) {
		pm.data = (uint8_t*)malloc(strlen(cmd->cmd())) ;
		memcpy(pm.data, cmd->cmd(), strlen(cmd->cmd())) ;
		pm.server = COMMAND ;
		pm.len = strlen(cmd->cmd()) ;
		uint32_t len = 0 ;
		uint8_t* pData = NULL ;
		pData = link->encode(pm, len) ;
		if(link->clientSend(pData, len)) {
//			link->clientRevc([](uint8_t * restr){
//				std::cout << restr << std::endl ;
//				return true ;
//			}) ;
		}
		
	}
	return true ;
}




int ComProgram::main(int argc, char **argv) {
	
	
	cl->getKeyValue(argc, argv) ;
	cc.init(cl->map) ;

	
	/*
	 * 连接服务器，失败退出
	 */
	if (!connectServer()) {
		log("err: can not connect linepasswd server.") ;
		return 1 ;
	}
	
	/*
	 * 信息认证
	 */
	if(!certify(link)) {
		link->linkClose() ;
		log("err: certify.") ;
		return 1;
	}
	
	
	if (!interactive()) {
		return 1 ;
	}
	return 0 ;
}

bool ComProgram::certify(LineLink* lk) {
	/*
	 *	转移用户信息
	 */
	
	struct user_config uc ; // struct.h
	struct proto_msg pm ; // link.hpp
	
//	uc.user_user = cc.connect_user ;
//	uc.user_password = cc.connect_password ;
	
	// 把用户信息复制到uc
	strcpy(uc.user_user, cc.connect_user.c_str()) ;
	strcpy(uc.user_password, cc.connect_password.c_str()) ;

	size_t size = sizeof(uc) ;
	char* plain = (char*)malloc(sizeof(char) * size) ;
	memcpy(plain,(char*)&uc,size) ;
	
   	std::string data = ECB_AESEncryptStr(aesKey,plain,size) ;
	pm.data = (uint8_t*)data.c_str() ;
	
	pm.len = data.size();
	pm.server = LOGIN ;
	uint32_t package_size;
	uint8_t* pdata = link->encode(pm, package_size) ;
	
	/*
	 *	发送登录验证信息
	 */
	if(!lk->clientSend(pdata, package_size)) {
		return false;
	}
	/*
	 *	返回报文
	 */
	return lk->clientRevc([&](struct proto_msg pm) {
		if (!strcmp((const char *)ls->decipher(pm.data), CALLBACKOK)) {
			return true ;
		}else {
			return false ;
		}
	}) ;
}

int ComProgram::main() {
	return 0 ;
}
