//
//  main.cpp
//  index
//
//  Created by Saber on 2018/4/19.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "lineprogram.hpp"
#include "secret.h"
int main(int argc, char * argv[]) {
      LineProgram* lp = new LineProgram() ;
      int retVal = lp->main(argc, argv) ;
      return retVal;
}
