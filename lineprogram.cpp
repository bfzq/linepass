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
//		std::cout << "this is help." << std::endl ;
		cl->printHelpInfo() ;
		return 0 ;
	}
	//	intoDameon() ; // xcode 编辑期间关闭
	getServerPara() ;
	initMysqlPool() ;
//	hideArg(argc,argv,"--password") ; // 隐藏密码
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

void LineProgram::hideArg(int argc, char **argv, const char *arg) {
	for (int i = 1; i < argc; i++) {
		if (0 == strcmp(argv[i], arg)) {
			for (int j = i + 1; j < argc; j++) {
				argv[i] = argv[j] ;
			}
			argv[argc - 1] = "" ;
			break ;
		}
	}
}


void LineProgram::initParameter(int argc, char **argv) {
	cl->getKeyValue(argc, argv) ;
}


void LineProgram::tasks() {
	link->listenPort(sc.listen_port) ;
	link->init() ;
	link->serverListen() ;
	link->serverAccpet([&](int client_socket) {
		
		
		//		if(mysqlc == nullptr) return false;
		
		/*
		 * 交互
		 */
		uint32_t byte = 0; // 返回长度
		uint8_t buf[PROTO_HEAD_SIZE] ; // 缓存
		while ((byte = recv(client_socket, buf, PROTO_HEAD_SIZE, 0)) > 0) { // 获取到客户端的数据 buf
			struct proto_head ph ;
			if(!link->parser(buf, byte, ph)) continue;
			if (ph.len > PROTO_HEAD_SIZE) {
				uint32_t datalen = ph.len - PROTO_HEAD_SIZE ;
				uint8_t* data = (uint8_t*)malloc(sizeof(uint8_t) * datalen) ;
				if ((byte = recv(client_socket, data, datalen, 0)) <= 0) {
					free(data) ;
					continue ;
				}
				switch (ph.server) {
					case LOGIN:{ // error:Cannot jump from switch statement to this case label # 因为switch case 中是不能定义对象的，因为只要是在大括号内定义的对象。所以只需要在case:后面加上大括号就OK
						/*
						 * 验证客户信息
						 */
						struct proto_msg pm ;
						pm.server = LOGIN ;
						uint32_t len ;
						ls->setKey(LINETESTKEY) ;
						uint8_t* unsafeData = ls->decipher(data) ;
						if(certify(unsafeData)) {
							uint8_t* retStr = ls->encrypt((unsigned char*)"ok") ;
							pm.len = AES::BLOCKSIZE ;
							pm.data = retStr ;
							//							memcpy(pm.data, retStr, pm.len) ;
						}else {
							uint8_t* retStr = ls->encrypt((unsigned char*)"err") ;
							pm.len = AES::BLOCKSIZE ;
							pm.data = retStr ;
							//							memcpy(pm.data, retStr, pm.len) ;
						}
						uint8_t* pdata = link->encode(pm, len) ;
						send(client_socket, pdata, len, 0) ;
						break;
					}
					case COMMAND:
						
						break ;
					default:
						break;
				}
				
				
				
			}
		}
		close(client_socket) ;
	}) ;
}

bool LineProgram::certify(uint8_t* buf) {
	struct user_config uc;
	bool retVal = false;
	memcpy(&uc, buf, sizeof(user_config)) ;
	MySQLC* local_mysql = mp->getMysqlCon() ;
	std::string sql = "select 1 from users where username='" + std::string(uc.user_user) + "' and password='" + std::string(uc.user_password) + "';" ;
	local_mysql->query(sql, [&retVal](MYSQL_ROW row) {
		if (atoi(row[0]) == 1) {
			std::cout << "1\n" ;
			retVal = true ;
			return true ;
		}else {
			retVal = false ;
			return false ;
		}
	}, [&retVal]() {
		retVal = false ;
	}) ;
	mp->backMysqlCon(local_mysql) ;
	local_mysql = nullptr ;
	
	return retVal ;
}

//bool LineProgram::certify(int client_socket) {
//	char buf[BUFSIZ] ;
//	struct user_config uc;
//	if (recv(client_socket, buf, BUFSIZ, 0) > 0) {
//		memcpy(&uc, buf, BUFSIZ) ;
//		std::cout << uc.user_user << ' ' << uc.user_password << std::endl ;
//		return true ;
//	}else {
//		return false ;
//	}
//}


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
