//
//  command.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "command.hpp"

// 判断是否是结束字符
bool equlEndSign(char c) {
	return ('\0' == c) ? true : false ;
}

/*对客户端的命令进行分解*/
bool Command::morphology() {
	char* word ;
	char* cmm_s = cmm;
//	memcpy(cmm_s, cmm, strlen(cmm)) ;
	com.empty() ;
	if (NULL != (word = strsep(&cmm_s, " "))) {
		com.gettype(word) ;
		switch (com.local_type) {
			case type::show:
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
			default:
				return false ;
		}
	} else {
		return false ;
	}
}

bool Command::checkMulti() {
	if ((type::put == com.local_type) && equlEndSign(com.ai.account[0]) && equlEndSign(com.ai.passwd[0])) {
		return true ;
	} else {
		return false ;
	}
}

void getline(char* s) {
	std::string str ;
	if (getline(std::cin, str)) {
		strcpy(s, str.c_str()) ;
	}
}

void checkAndGetString(char*name, char* info) {
	if (equlEndSign(info[0])) {
		printf("%s: ",name) ;
		getline(info) ;
	}
}

void Command::multiInput() {
	checkAndGetString("title", com.ai.title) ;
	checkAndGetString("nickname", com.ai.nickname) ;
	checkAndGetString("company", com.ai.company) ;
	checkAndGetString("account", com.ai.account) ;
	checkAndGetString("passwd", com.ai.passwd) ;
}

bool Command::input() {
	std::cout << "# " ;
	std::string s ;
	if(getline(std::cin, s)) {// 输入正常则返回true
		strcpy(cmm, s.c_str()) ;
		if (morphology()) {
			if (checkMulti()) {
				multiInput() ;
			}
			return true ;
		} else {
			return false ;
		}
	}
	return false ;
}

struct command Command::cmd() {
	return com ;
}
