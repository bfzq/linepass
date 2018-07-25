//
//  comprogram.hpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef comprogram_hpp
#define comprogram_hpp
#include "mainprogram.hpp"
#include "const.h"
#include "linesecret.hpp"
#include "link.hpp"
#include "comline.hpp"
#include "command.hpp"
#include "struct.h"
#include <string>
#include "logs.hpp"
#include "secret.h"


#define CONNECTPORT "line-port"
#define CONNECTHOST "line-host"
#define CONNECTUSER "line-user"
#define CONNECTPASSWORD "line-passwd"
//#define <#macro#>

extern const unsigned char* LINETESTKEY ;


struct client_config {
	int connect_port ;
	std::string connect_host ;
	std::string connect_user ;
	std::string connect_password ;
	client_config() {};
	client_config(std::map<std::string, std::string>*) ;
	void init(std::map<std::string, std::string>*) ;
};

class ComProgram : public MainProgram {
private:
	LineLink* link ;
//	ComLine* lc ;
	LineSecret* ls ;
	Command* cmd ;
	struct client_config cc ; // 连接信息
//	struct user_config uc ; // 登录用户信息
private:
	bool certify(LineLink*) ;
	bool connectServer() ;
	bool interactive() ;
public:
	ComProgram() ;
	~ComProgram() ;
public:
	int main(int argc, char* argv[]) ;
	int main() ;
};

#endif /* comprogram_hpp */
