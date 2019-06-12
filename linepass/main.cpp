//
//  main.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/4/27.
//  Copyright © 2018年 Saber. All rights reserved.
//
//
#include <iostream>
#include "comprogram.hpp"

int main(int argc,char* argv[]) {
  ComProgram *cp = new ComProgram();
  int retVal = cp->main(argc, argv);
  delete cp;
  cp = nullptr;
  return retVal;
}
