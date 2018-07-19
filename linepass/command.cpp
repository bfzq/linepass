//
//  command.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "command.hpp"


bool Command::input() {
	std::cout << "# " ;
	std::string s ;
	if(getline(std::cin, s)) {// 输入正常则返回true
		strcpy(cmm, s.c_str()) ;
		return morphology() ;
	}
	return false ;
}


bool Command::morphology() {
	// [CODE]
	return true ;
}


char* Command::cmd() {
	return cmm ;
}
