//
//  struct.h
//  LinePassword
//
//  Created by 猪摇摇 on 2018/6/8.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef struct_h
#define struct_h
#include <string>
#include <ctime>

#define CALLBACKOK "ok"
#define CALLBACKERR "err"
//#define LOGIN 0
//#define COMMAND 1

struct user_config {
	char user_user[256];
	char user_password[256];
};
struct accountinfo {
	char title[64] ;
	char company[128] ;
	char account[256] ;
	char passwd[256] ;
	char nickname[64] ;
};


enum type : ushort {show = 0,put,del,search,quit,ty_zero} ;
enum subtype : ushort {all = 0,tittle,company,account,nickname,sub_zero} ;
const char type_s[5][7] = {"show","put","del","search","quit"} ;
const char subtype_s[5][9] = {"all","title","company","account","nickname"} ;

/*
 *	show title:第一个标题
 *	search nickname:小红
 *	put account:adasd passwd:asdasd
 *	del no:1
 */
struct command {
	type type; // 0 show, 1 put , 2 search
	subtype sutype;
	char content[256] ; //a content what used by 'show' or 'search'
	struct accountinfo ai ; // used by put
	
	void gettype(char* ty) {
		ushort i ;
		for(i = 0; i < 5; i++) {
			if(0 == strcmp(type_s[i], ty)) {
				type = (enum type)i;
				break ;
			}
		}
		if (i == 5) type = type::ty_zero;
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
				sutype = (enum subtype)i;
				break ;
			}
		}
		if (i == 5) sutype = subtype::sub_zero;
	}
};








#endif /* struct_h */
