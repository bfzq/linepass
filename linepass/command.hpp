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
	char cmm[256] ;
	struct command com ;
private:
	bool morphology() ;
public:
	bool input() ;
//	char* cmd() ;
	struct command cmd() ;
};
#endif /* command_hpp */
