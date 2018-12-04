//
//  granalysis.hpp
//  index
//	语法解析
//  Created by 猪摇摇 on 2018/11/13.
//  Copyright © 2018 bfzq. All rights reserved.
//

#ifndef granalysis_hpp
#define granalysis_hpp

#include <string>
#include "list.hpp"
#include "struct.h"
class Granalysis {
public:
	Granalysis(std::string cmd) ;
	Granalysis() = default ;
public:
	command getStructCmd() ;
private:
	command _cmd ; // 结构化命令
	std::string _cmdStr ; // 命令
public:
	bool morphology(std::string cmd) ;
	bool morphology() ;
};

#endif /* granalysis_hpp */
