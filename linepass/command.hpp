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
#include <string.h>
//#include <stdio.h>
#include "struct.h"
#include <functional>




class Command {
private:
//	bool multiEnable ; // 多行输入
	char cmm[256] ;
	struct command com ;
private:
	bool morphology() ;
	bool checkMulti() ; // 检测是否需要多行输入
	void multiInput() ; // 多行输入
public:
	bool input() ;
//	char* cmd() ;
	struct command cmd() ;
};
#endif /* command_hpp */
