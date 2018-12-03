//
//  command.hpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef command_hpp
#define command_hpp

#include <iostream>
#include <string>
#include <algorithm>
//#include <stdio.h>
#include "struct.h"
#include <functional>
#include "list.hpp"

#define _QUIT_ "quit"
#define _SLASH_Q_ "\\q"
#define _EXIT_ "exit"



class Command {
private:
//	bool multiEnable ; // 多行输入
	bfzq::List<Field> _field_list ;
	std::string _cmm;
//	struct command com ;
private:
//	bool morphology() ;
//	bool checkMulti() ; // 检测是否需要多行输入
//	void multiInput() ; // 多行输入
public:
	bool input() ;
	void setCommandStruct(bfzq::List<Field>) ;
//	char* cmd() ;
//	struct command cmd() ;
//	bfzq::List<Field> getCmd() ;
	uint8_t* getSol() ; // 获取结构化操作语言
	std::string getCmm() ;
};
#endif /* command_hpp */
