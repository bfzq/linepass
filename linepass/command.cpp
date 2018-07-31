//
//  command.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "command.hpp"

//int m() {
//
//}

/*对客户端的命令进行分解*/
bool Command::morphology() {
	char* word ;
	char* cmm_s = cmm;
//	memcpy(cmm_s, cmm, strlen(cmm)) ;
	com.local_type = type::ty_zero ;
	if (NULL != (word = strsep(&cmm_s, " "))) {
		com.gettype(word) ;
		switch (com.local_type) {
			case type::put: {
				while (NULL != (word = strsep(&cmm_s, " "))) {
					char* accountkey ;
					if (NULL != (accountkey = strsep(&word, ":"))) {
						if (0 == strcmp(accountkey, "title")) {
							memcpy(com.ai.title, word, strlen(word)) ;
						} else if (0 == strcmp(accountkey, "account")) {
							memcpy(com.ai.account, word, strlen(word)) ;
						} else if (0 == strcmp(accountkey, "passwd")) {
							memcpy(com.ai.passwd, word, strlen(word)) ;
						} else if (0 == strcmp(accountkey, "nickname")) {
							memcpy(com.ai.nickname, word, strlen(word)) ;
						} else if(0 == strcmp(accountkey, "company")) {
							memcpy(com.ai.company, word, strlen(word)) ;
						}
					}
				}
				return true ;
			}
			case type::quit: {
				return true ;
			}
			case type::show: {
				char* subkey ;
				if (NULL != (subkey = strsep(&cmm_s, ":"))) {
					
				}
			}
			default:
				return false ;
		}
	} else {
		return false ;
	}
}

bool Command::input() {
	std::cout << "# " ;
	std::string s ;
	if(getline(std::cin, s)) {// 输入正常则返回true
		strcpy(cmm, s.c_str()) ;
		return morphology() ;
	}
	return false ;
}


//bool Command::morphology() {
//	calcommand(cmm, [&](enum type ty, enum  subtype sub, char* value) {
//		if (0 == strcmp(type, "quit") or 0 == strcmp(type, "q")) {
//			com.type = type::quit ;
//			return ;
//		}else {
////			com.type =
//		}
//	}) ;
//
//	return true ;
//}


struct command Command::cmd() {
	return com ;
}
