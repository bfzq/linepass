//
//  mainprogram.cpp
//  LinePassword
//
//  Created by Saber on 2018/4/23.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "mainprogram.hpp"

void MainProgram::hideArg(int argc, char **argv, const char *arg) {
//        for (int i = 1; i < argc; i++) {
//                if (0 == strcmp(argv[i], arg)) {
//                	memset(argv[i], 'x', strlen(argv[i]));
//			break ;
//		}
//        }
	unsigned int idx = cl->findParamIndex(argc,argv,std::string(arg)) ;
	memset(argv[idx], 'x', strlen(argv[idx]));
}


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
