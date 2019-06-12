//
//  mystring.hpp
//  index
//
//  Created by 猪摇摇 on 2018/12/2.
//  Copyright © 2018 bfzq. All rights reserved.
//

#ifndef mystring_hpp
#define mystring_hpp

#include <stdio.h>
#include <string>

class MyString : public std::string {
public:
  std::string operator()(int a);
};

#endif /* mystring_hpp */
