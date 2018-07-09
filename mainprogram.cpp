//
//  mainprogram.cpp
//  LinePassword
//
//  Created by Saber on 2018/4/23.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "mainprogram.hpp"


MainProgram::MainProgram() {
	cl = new ComLine() ;
}

MainProgram::~MainProgram() {
	delete cl ;
	cl = nullptr ;
}

int MainProgram::main(int argc, char **argv) {
	if(cl->getKeyValue(argc, argv)) {
		return 0 ;
	} else {
		return 1 ;
	}
}


int MainProgram::main() {
	std::cout << "this is MainProgram main" << std::endl ;
	return 0 ;
}
