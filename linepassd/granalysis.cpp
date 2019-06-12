//
//  granalysis.cpp
//  index
//
//  Created by 猪摇摇 on 2018/11/13.
//  Copyright © 2018 bfzq. All rights reserved.
//

#include "granalysis.hpp"

Granalysis::Granalysis(std::string cmd) 
{
  _cmdStr = cmd;
}

command Granalysis::getStructCmd() 
{
  return _cmd;
}

// 语法解析错误则返回false
bool Granalysis::morphology(std::string cmd) 
{
  _cmd.list.clean();
  std::string::size_type idx = 0; // 开始位置
  std::string::size_type edx = 0; // 结束位置
  std::string linelan = cmd;
  unsigned i = 0;
  do {
    edx = linelan.find_first_of(" ", idx);  // 查找从idx开始出现的第一个字符串位置edx
    std::string tmp_s = linelan.substr(idx, edx - idx);
    if (i == 0) {
      if (!_cmd.gettype(tmp_s.c_str())) return false;
    } else {
      _cmd.list.Insert(Field(tmp_s, ":"));
    }
    idx = edx + 1;
    i++;
  } while (edx != linelan.npos);
  return true;
}


bool Granalysis::morphology() {
  return morphology(_cmdStr);
}
