//
//  struct.h
//  LinePassword
//
//  Created by 猪摇摇 on 2018/6/8.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef struct_h
#define struct_h
#include <netinet/in.h>
#include <string>
#include <ctime>

#define CALLBACKOK "ok"
#define CALLBACKERR "err"


#define TITLESIZE 64
#define COMPANYSIZE 128
#define ACCOUNTSIZE 256
#define PASSWDSIZE 256
#define NICKNAMESIZE 64
#define CONTENTSIZE 256
//#define LOGIN 0
//#define COMMAND 1

struct user_config {
	int user_id ;
	char user_user[256];
	char user_password[256];
};
struct accountinfo {
	char title[TITLESIZE] = {'\0'};
	char company[COMPANYSIZE]  = {'\0'};
	char account[ACCOUNTSIZE]  = {'\0'};
	char passwd[PASSWDSIZE]  = {'\0'};
	char nickname[NICKNAMESIZE]  = {'\0'};
	void empty() {
		title[0] = '\0' ;
		company[0] = '\0' ;
		account[0] = '\0' ;
		passwd[0] = '\0' ;
		nickname[0] = '\0' ;
	}
};


enum type: uint16_t {show,put,del,search,quit,result, ty_zero} ;
enum subtype: uint16_t {all,tittle,company,account,nickname,sub_zero} ;
const char type_s[5][7] = {"show","put","del","search","quit"} ;
const char subtype_s[5][9] = {"all","title","company","account","nickname"} ;

/*
 *	show title:第一个标题
 *	search nickname:小红
 *	put account:adasd passwd:asdasd
 *	del no:1
 */
struct command {
	enum type local_type; // 0 show, 1 put , 2 search
	enum subtype local_sutype;
	char content[CONTENTSIZE] ; //a content what used by 'show' or 'search'
	struct accountinfo ai ; // used by put
	
	// 拆除函数
	uint8_t* disassemble() {
		static uint8_t disass[1030] ; // 拆解存储器
		*((uint16_t*)disass) = htons(local_type) ;
		*((uint16_t*)(disass + 2)) = htons(local_sutype) ;
		memcpy(disass + 4, content, CONTENTSIZE) ;
		memcpy(disass + 4 + CONTENTSIZE, (uint8_t*)ai.title, TITLESIZE) ;
		memcpy(disass + 4 + CONTENTSIZE + TITLESIZE, (uint8_t*)ai.company, COMPANYSIZE) ;
		memcpy(disass + 4 + CONTENTSIZE + TITLESIZE + COMPANYSIZE, (uint8_t*)ai.account, ACCOUNTSIZE) ;
		memcpy(disass + 4 + CONTENTSIZE + TITLESIZE + COMPANYSIZE + ACCOUNTSIZE, (uint8_t*)ai.passwd, PASSWDSIZE) ;
		memcpy(disass + 4 + CONTENTSIZE + TITLESIZE + COMPANYSIZE + ACCOUNTSIZE + PASSWDSIZE, (uint8_t*)ai.nickname, NICKNAMESIZE) ;
		return disass ;
	}
	
	// 装配函数
	void assemble(uint8_t* disass) {
		local_type = (type)ntohs(*((uint16_t*)disass)) ;
		local_sutype = (subtype)ntohs(*((uint16_t*)(disass + 2))) ;
		memcpy(content,disass + 4, CONTENTSIZE) ;
		memcpy(ai.title, disass + 4 + CONTENTSIZE, TITLESIZE) ;
		memcpy(ai.company, disass + 4 + CONTENTSIZE + TITLESIZE, COMPANYSIZE) ;
		memcpy(ai.account, disass + 4 + CONTENTSIZE + TITLESIZE + COMPANYSIZE, ACCOUNTSIZE) ;
		memcpy(ai.passwd, disass + 4 + CONTENTSIZE + TITLESIZE + COMPANYSIZE + ACCOUNTSIZE, PASSWDSIZE) ;
		memcpy(ai.nickname, disass + 4 + CONTENTSIZE + TITLESIZE + COMPANYSIZE + ACCOUNTSIZE + PASSWDSIZE, NICKNAMESIZE) ;
	}
	
	void empty() {
		ai.empty() ;
		local_type = type::ty_zero ;
		content[0] = '\0' ;
		local_sutype = subtype::all ;
	}
	void gettype(char* ty) {
		ushort i ;
		for(i = 0; i < 5; i++) {
			if(0 == strcmp(type_s[i], ty)) {
				local_type = (enum type)i;
				break ;
			}
		}
		if (i == 5) local_type = type::ty_zero;
	}
	
	
// 重载操作符
//	void operator =(char* ty) {
//		for(ushort i = 0; i < 5; i++) {
//			if(0 == strcmp(type_s[i], ty)) {
//				type = (enum type)i;
//			}
//		}
//		type = type::ty_zero;
//	}
	
	void getsubtype(char* ty) {
		ushort i ;
		for(i = 0; i < 5; i++) {
			if(0 == strcmp(subtype_s[i], ty)) {
				local_sutype = (enum subtype)i;
				break ;
			}
		}
		if (i == 5) local_sutype = subtype::sub_zero;
	}
};








#endif /* struct_h */
