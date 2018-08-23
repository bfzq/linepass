//
//  lineprogram.cpp
//  LinePassword
//
//  Created by Saber on 2018/4/23.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "lineprogram.hpp"


server_config::server_config(std::map<std::string, std::string>* m) {
	init(m) ;
}

void server_config::init(std::map<std::string, std::string> * m) {
	listen_port = atoi((*m)[LISTENPORT].c_str()) ;
	poolnum = atoi((*m)[POOLNUM].c_str()) ;
}

LineProgram::LineProgram() {
	ls = new LineSecret() ;
	link = new LineLink(LineLink::SERVER) ;
	mp = new MysqlcPool() ;
}

LineProgram::~LineProgram() {
	delete ls;
	delete link ;
	delete mp ;
}

int LineProgram::main(int argc, char **argv) {
	initParameter(argc, argv) ;
	if (cl->haveHelp()) {
		cl->printHelpInfo() ;
		return 0 ;
	}
//	intoDameon() ; // xcode 编辑期间关闭
	getServerPara() ;
	initMysqlPool() ;
	hideArg(argc,argv,"mysql-passwd") ; // 隐藏密码
	tasks() ;
	return 0 ;
}


/*
 *    初始化mysql连接池
 */
void LineProgram::initMysqlPool() {
	mp->init(mc, sc.poolnum) ;
}


void LineProgram::getServerPara() {
	sc.init(cl->map) ;
	mc.init(cl->map) ;
}


void LineProgram::initParameter(int argc, char **argv) {
	cl->getKeyValue(argc, argv) ;
}


bool LineProgram::certify(struct user_config* uc, int8_t* buf) {
//	struct user_config uc;
	bool retVal = false;
	memcpy(uc, buf, sizeof(user_config)) ;
	//	printf("user:%s,password:%s\n",uc.user_user,uc.user_password) ;
	MySQLC* local_mysql = mp->getMysqlCon() ;
	std::string sql = "select id,password from users where username='" + std::string((*uc).user_user) + "' limit 1" ;
	local_mysql->query(sql, [&retVal,&uc](MYSQL_ROW row) {
		if (strcmp((*uc).user_password, ECB_AESDecryptStr(aesDbKey,row[1]).c_str()) == 0) {
			(*uc).user_id = atoi(row[0]) ;
			retVal = true ;
		}else {
			retVal = false ;
		}
		return true ;
	}, [&retVal]() {
		retVal = false ;
	}) ;
	mp->backMysqlCon(local_mysql) ;
	local_mysql = nullptr ;
	////	retVal = true ;
	return retVal ;
}


void LineProgram::commandWork(struct user_config* uc, int client_socket,int8_t *cmd) {
	struct command comma;
	memcpy(&comma, cmd, sizeof(comma)) ;
	switch (comma.local_type) {
		case type::put:
			try {
				MySQLC* local_mysql = mp->getMysqlCon() ;
				local_mysql->begin() ;
				std::string sql_company = "insert into company(ps_name) value(' "
				+ std::string(comma.ai.company)
				+ " ')" ;
				local_mysql->query(sql_company) ;
				
				std::string sql_account = "insert into accounts(user_id,company_id,account,passwd) value("
				+ std::to_string((*uc).user_id) + " , last_insert_id(),' " + std::string(comma.ai.account)
				+ "' , '"
				+ ECB_AESEncryptStr(aesDbKey, comma.ai.passwd, strlen(comma.ai.passwd))
				+ "')";
				
				local_mysql->query(sql_account) ;
				local_mysql->commit() ;
				
				/*
				 * 返回客户信息
				 */
				struct proto_msg pm ;
				pm.server = COMMAND ;
				std::string backinfo = "PUT IS SUCCESS" ;
				// 返回报文加密
				std::string sedata = ECB_AESEncryptStr(aesKey, backinfo.c_str(), backinfo.size()) ;
				pm.data = (int8_t*)sedata.c_str() ;
				pm.len = sedata.size() ;
				uint32_t len ; // 网络报文长度
				
				uint8_t* pdata = link->encode(pm, len) ;
				send(client_socket, pdata, len, 0) ;
				
				mp->backMysqlCon(local_mysql) ;
				local_mysql = nullptr ;
				
			} catch (MySQLC* local_mysql) {
				local_mysql->rollback() ;
				mp->backMysqlCon(local_mysql) ;
				local_mysql = nullptr ;
				
				/*
				 * 返回客户信息
				 */
				struct proto_msg pm ;
				pm.server = COMMAND ;
				std::string backinfo = "PUT IS ERROR" ;
				// 返回报文加密
				std::string sedata = ECB_AESEncryptStr(aesKey, backinfo.c_str(), backinfo.size()) ;
				pm.data = (int8_t*)sedata.c_str() ;
				pm.len = sedata.size() ;
				uint32_t len ; // 网络报文长度
				
				uint8_t* pdata = link->encode(pm, len) ;
				send(client_socket, pdata, len, 0) ;
				
				
			}
			
			
			
//			std::string sql = "insert into "
			break;
			
		default:
			break;
	}
	
}


void LineProgram::tasks() {
	link->listenPort(sc.listen_port) ;
	link->init() ;
	link->serverListen() ;
	link->serverAccpet([&](int client_socket) {
		struct user_config uc ;
		/*
		 * 交互
		 */
		uint32_t byte = 0; // 返回长度
		uint8_t buf[PROTO_HEAD_SIZE] ; // 缓存
		while ((byte = recv(client_socket, buf, PROTO_HEAD_SIZE, 0)) > 0) { // 获取到客户端的数据 buf
			struct proto_head ph ;
			if(!link->parser(buf, byte, &ph)) continue;
			if (ph.len > PROTO_HEAD_SIZE) {
				uint32_t datalen = ph.len - PROTO_HEAD_SIZE ;
				int8_t* data = (int8_t*)malloc(sizeof(int8_t) * (datalen + 1)) ;
				if ((byte = recv(client_socket, data, datalen, 0)) <= 0) {
					free(data) ;
					continue ;
				}
				data[datalen] = '\0' ;
				
				/*
				 *	解密数据包
				 */
				int8_t* unsafeData = (int8_t*)ECB_AESDecryptStr(aesKey,(const char*)data).c_str() ;
				free(data) ;	
				
				switch (ph.server) {
					// 登录验证
					case LOGIN:{ // error:Cannot jump from switch statement to this case label \
						# 因为switch case 中是不能定义对象的，因为只要是在大括号内定义的对象。\
						所以只需要在case:后面加上大括号就OK.
						
						// 记录返回报文
						std::string backtext ;
						// 验证数据包
						if(certify(&uc, unsafeData)) {
							// 验证成功，返回ok
							backtext = CALLBACKOK ;
						}else {
							// 验证成功，返回err
							backtext = CALLBACKERR ;
						}
						
						/*
						 * 返回客户信息
						 */
						struct proto_msg pm ;
						pm.server = LOGIN ;
						// 返回报文加密
						std::string sedata = ECB_AESEncryptStr(aesKey, backtext.c_str(), backtext.size()) ;
						pm.data = (int8_t*)sedata.c_str() ;
						pm.len = sedata.size() ;
						uint32_t len ; // 网络报文长度
						
						uint8_t* pdata = link->encode(pm, len) ;
						send(client_socket, pdata, len, 0) ;
						break;
					}
					case COMMAND:
						commandWork(&uc,client_socket,unsafeData) ;
						break ;
					default:
						break;
				}
				
				
				
			}
		}
		close(client_socket) ;
	}) ;
}


int LineProgram::main() {
	//	intoDameon() ; // xcode 编辑期间关闭
	return 0;
}


bool LineProgram::intoDameon() {
	pid_t pc;
	pc = fork(); /*第一步:创建子进程*/
	if(pc<0){
		return false ;
	}else if(pc>0){//父进程退出
		exit(0);
	}
	if(setsid() < 0) {
		return false ;
	} else {
		return true ;
	}/*第二步:在子进程中创建新会话*/
}
