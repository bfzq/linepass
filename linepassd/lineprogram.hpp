//
//  lineprogram.hpp
//  LinePassword
//
//  Created by Saber on 2018/4/23.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef lineprogram_hpp
#define lineprogram_hpp
#include "../common/mainprogram.hpp"
#include "../common/linesecret.hpp"
#include "../common/link.hpp"
#include "mysqlc.h"
#include <unistd.h>
#include "comline.hpp"
#include "struct.h"
#include "mysqlcpool.hpp"
#include "secret.h"
#include "const.h"
//#include "linedata.hpp"
#include <stdlib.h>
#include "granalysis.hpp"
//#include "json.h"
#include "netstruct.hpp"



#define LISTENPORT "listen-port"
#define POOLNUM "pool-num"


extern const unsigned char* LINETESTKEY ;



struct server_config {
	int listen_port ;
	uint16_t poolnum ;
	server_config() {};
	server_config(std::map<std::string, std::string>*) ;
	void init(std::map<std::string, std::string>*) ;
};

class LineProgram : public MainProgram {
private:
	struct server_config sc ; // 系统参数
	LineSecret* ls ; // 加密
	LineLink* link ; // 网络
    MysqlcPool* mp ; // mysql连接池
	struct mysql_config mc ; // mysql 连接信息
	Granalysis granalysis ; // 语法解析器
public:
	LineProgram() ;
	~LineProgram() ;
public:
	int main(int argc, char* argv[]) ;
	int main() ;
private:
	void initMysqlPool() ;
	bool intoDameon() ; //守护程序
	void tasks() ;
	void initParameter(int argc, char* argv[]) ;
	void getServerPara() ;
//	bool certify(int) ;
	bool certify(struct user_config*, uint8_t*) ;
	// 返回客户端消息
	void feedBack(int client_socket, Server server , const char* unsafedata, size_t datasize) ;
//	void hideArg(int argc, char** argv, const char* arg) ;
private:
	void commandWork(struct user_config* uc, int client_socket, uint8_t* cmd) ;
private:
	void showUserAccount(struct command comma, struct user_config* uc, int client_socket) ; // 查询用户帐号
	void putAccountToServer(struct command comma, struct user_config* uc, int client_socket) ; // 添加用户帐号
	void editAccount(struct command comma, struct user_config* uc, int client_socket) ;
};

#endif /* lineprogram_hpp */
