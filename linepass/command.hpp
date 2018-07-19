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



class Command {
private:
	char cmm[256] ;
private:
	bool morphology() ;
public:
	bool input() ;
	char* cmd() ;
};
#endif /* command_hpp */
