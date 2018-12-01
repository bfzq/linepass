//
//  link.hpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef link_hpp
#define link_hpp
#include "const.h"
#include "secret.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "stdio.h"
#include <arpa/inet.h>
#include <string.h>




#include "threadpool.h"
#include <functional>


//#include "struct.h"

#define MAXQUEUE 20
const uint8_t PROTO_MAGIC = 'L';
const uint32_t PROTO_HEAD_SIZE = 8 ;
const uint8_t PROTO_VERSION = '1' ;

enum Server: uint16_t {LOGIN, COMMAND, MESSAGE, RESULT,DONE};

/*
 *	总长 8 byte
 */
struct proto_head {
	uint8_t version ; // 协议版本号 1 byte
	uint8_t magic; // magic number 1 byte
	Server server ; // 标识服务 2 byte 1:字符串
	uint32_t len ; // 报文长度 4 byte
//	uint32_t testLen ; // 内容长度
};

struct proto_msg {
	uint32_t len ; // 结构体长度
	Server server ; // 标识服务 2 byte 1:字符串
	uint8_t* data ; // 加密数据
	proto_msg() = default ;
	proto_msg(const proto_msg& mg) {
		len = mg.len ;
		server = mg.server ;
		data = (uint8_t*)malloc(sizeof(uint8_t) * (len + 1)) ;
		memcpy(data, mg.data, len + 1) ;
	}
	
	proto_msg(Server s, const uint8_t* dat, size_t datasize) {
		server = s ;
		len = datasize ;
		data = (uint8_t*)malloc(sizeof(uint8_t) * (datasize + 1)) ;
		memcpy(data, dat, len + 1) ;
	}
	
	~proto_msg() {
		if (data) {
			free(data) ;
			data = nullptr ;
		}
	}
};



class LineLink {
public:
	enum JOB{SERVER,CLIENT}; // 服务器角色 or 客户端角色
private:
	fivestar::ThreadPool threadPool; // 多线程
	int local_socket ; // 本地套接字和客户端套接字
	struct sockaddr_in server_addr, client_addr; // #include <netinet/in.h> 网络地址结构体
	JOB job ;
private:
	void listenOrConnectPort(in_port_t) ;
public:
	LineLink() ;
	LineLink(JOB) ;
	~LineLink() ;
	
	bool init() ; // 初始化套接字和网络
	void listenPort(in_port_t) ;
	/* 服务器函数 */
	bool serverListen() ; // 监听客户端连接请求
	bool serverAccpet(std::function<void (int)> recv_block) ; // 等待客户端连接请求
	/* 客户端函数 */
	void clientHost(std::string host) ;
//	void clientRecv() ;
	void clientPort(in_port_t) ;
	bool clientConnect() ;
	
	bool clientRevc(std::function<void(struct proto_msg)> revc);
	
	
	bool clientSend(uint8_t* buf,size_t size) ;
	/* 关闭连接 */
	bool linkClose() ;
	
	
	/* 网络协议打包 */
	uint8_t* encode(struct proto_msg, uint32_t& len) ;
	/* 网络协议解包 */
	bool parser(uint8_t*,uint32_t, struct proto_head*) ;
};

#endif /* link_hpp */
