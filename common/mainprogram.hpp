//
//  mainprogram.hpp
//  LinePassword
//
//  Created by Saber on 2018/4/23.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef mainprogram_hpp
#define mainprogram_hpp
#include "comline.hpp"
#include <string.h>
class MainProgram {
protected:
  ComLine* cl;
public:
  MainProgram();
  virtual ~MainProgram();
public:
  virtual int main(int argc, char* argv[]);
  virtual int main();
  void hideArg(int argc, char **argv, const char *arg);
};

#endif /* mainprogram_hpp */
