//
//  main.cpp
//  index
//
//  Created by Saber on 2018/4/19.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include <iostream>
//#include <unistd.h>
#include "lineprogram.hpp"

int main(int argc, char * argv[]) {
      LineProgram* lp = new LineProgram();
      int retVal = lp->main(argc, argv);
      return retVal;
//
//    mysql_config mf;
//    mf.db = "linepass";
//    mf.heart_time = 3;
//    mf.host = "127.0.0.1";
//    mf.passwd = "123456";
//    mf.port = 3306;
//    mf.user = "root";

//    MysqlcPool mp;
//    mp.init(mf,8);
//    mp->keepAlive();
//    getchar();
//    return 0;
    
}
