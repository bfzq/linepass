//
//  link.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "link.hpp"


LineLink::LineLink() {
	
}

LineLink::~LineLink() {
	
}


LineLink::LineLink(JOB job) {
	this->job = job ;
	switch (this->job) {
		case SERVER:
			server_addr.sin_family = AF_INET ; // 设置为IP通信
			server_addr.sin_addr.s_addr = INADDR_ANY ; // 服务器IP地址--允许连接到所有本地地址上
			break;
		case CLIENT:
			server_addr.sin_family = AF_INET ;
			break;
	}
}


void LineLink::listenOrConnectPort(in_port_t port) {
	server_addr.sin_port = htons(port) ;
	//	server_addr.sin_addr
}

void LineLink::listenPort(in_port_t port) {
	listenOrConnectPort(port) ;
}

void LineLink::clientPort(in_port_t port) {
	listenOrConnectPort(port) ;
}


bool LineLink::init() {
	switch (job) {
		case SERVER:{
			int flag = 1 ;
			if ((local_socket = socket(PF_INET,SOCK_STREAM,0)) < 0 // 创建服务器端套接字--IPv4协议，面向连接通信，TCP协议
				|| setsockopt(local_socket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0
				|| bind(local_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0 // 将套接字绑定到服务器的网络地址上
				) {
				perror("init error") ;
				return false ;
			}
			threadPool.setMaxQueueSize(MAXQUEUE) ;
			threadPool.start(MAXQUEUE) ;
			break ;
		}
		case CLIENT:
			if ((local_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
				perror("socket error") ;
				return false ;
			}
			break;
	}
	return true ;
}





bool LineLink::serverListen() {
	if (listen(local_socket, 5) < 0) {
		perror("listen error") ;
		return false ;
	}
	return true ;
}


bool LineLink::serverAccpet(std::function<void (int)> recv_block) {
	while (true) {
		int sin_size = sizeof(struct sockaddr_in) ;
		int remote_socket ;
		if ((remote_socket = accept(local_socket, (struct sockaddr *)&client_addr, (socklen_t *)&sin_size)) < 0) {
			perror("accpet error") ;
			return false ;
		}
		threadPool.run(std::bind(recv_block, remote_socket)) ;
	}
	return true ;
}


bool LineLink::linkClose() {
	close(local_socket) ;
	return true ;
}

/* client */


void LineLink::clientHost(std::string host) {
	server_addr.sin_addr.s_addr = inet_addr(host.c_str()) ;
}


bool LineLink::clientConnect() {
	if (connect(local_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0) {
		perror("connect error") ;
		return false ;
	}
	return true ;
}


bool LineLink::clientRevc(std::function<void (struct proto_msg)> revc) {
	uint32_t len ;
	uint8_t buf[PROTO_HEAD_SIZE];
	if((len=recv(local_socket,buf,PROTO_HEAD_SIZE,0))) { //接收服务器端信息
		struct proto_head ph ;
		if (!parser(buf, len, &ph)) {
			return false ;
		}
		if (ph.len > PROTO_HEAD_SIZE) {
			uint32_t datalen = ph.len - PROTO_HEAD_SIZE ;
			int8_t* data = (int8_t*)malloc(sizeof(int8_t) * (datalen + 1)) ;
			if ((len = recv(local_socket, data, datalen, 0)) > 0) {
				data[datalen] = '\0' ;
				if (len == ph.len - PROTO_HEAD_SIZE) {
					struct proto_msg pm ;
					pm.server = ph.server ;
					pm.len = len ;
					pm.data = data ;
					revc(pm) ;
				}
			}
		}
	}
	return true ;
}


bool LineLink::clientSend(uint8_t* buf, size_t size) {
	if (send(local_socket,buf,size,0)) {
		return true ;
	}
	perror("send text err.") ;
	return false ;
}

uint8_t* LineLink::encode(struct proto_msg pm, uint32_t& len) {
	len = PROTO_HEAD_SIZE + pm.len ;
	uint8_t* buf = (uint8_t*)malloc(sizeof(uint8_t) * len) ;
	*buf = PROTO_VERSION ; //
	*(buf + 1) = PROTO_MAGIC ; //
	*((uint16_t*)(buf + 2)) = htons(pm.server) ; //
	*((uint32_t*)(buf + 4)) = htonl(len) ;
	memcpy(buf + PROTO_HEAD_SIZE, pm.data, pm.len) ;
	return buf ;
}


bool LineLink::parser(uint8_t * buf,uint32_t getlen, struct proto_head *ph) {
	if (getlen < PROTO_HEAD_SIZE) {
		return false ;
	}
	(*ph).version = *(buf) ;
	(*ph).magic = *(buf + 1) ;
	if ((*ph).magic != PROTO_MAGIC) {
		return false ;
	}
	(*ph).server = (Server)ntohs(*((uint16_t*)(buf + 2))) ;
	(*ph).len = ntohl(*((uint32_t*)(buf + 4))) ;
	return true ;
}
