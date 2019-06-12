//
//  command.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "command.hpp"

//// 判断是否是结束字符
//bool equlEndSign(char c) {
//  return ('\0' == c) ? true : false;
//}
//
//
//
///*对客户端的命令进行分解*/
//bool Command::morphology() {
//  std::string::size_type idx = 0; // 开始位置
//  std::string::size_type edx = 0; // 结束位置
//  std::string linelan = cmm;
//  linelan.erase(linelan.length() - 1);
//  do {
//    edx = linelan.find_first_of(" ", idx);  // 查找从idx开始出现的第一个字符串位置edx
//    std::string tmp_s = linelan.substr(idx, edx - idx);
//    _field_list.Insert(Field(tmp_s, ":"));
//    idx = edx + 1;
//  } while (edx != linelan.npos);
//  return true;
//}
//
//
//// 检查是否是输入，且包含帐号或者密码
//bool Command::checkMulti() {
//  if ((type::put == com.local_type) && (equlEndSign(com.ai.account[0]) || equlEndSign(com.ai.passwd[0]))) {
//    return true;
//  } else {
//    return false;
//  }
//}

//// 获取输入信息
//void getline(char* s) {
//  std::string str;
//  if (getline(std::cin, str)) {
//    strcpy(s, str.c_str());
//  }
//}
//
//// 逐行获取输入信息
//void checkAndGetString(char*name, char* info) {
//  if (equlEndSign(info[0])) {
//    printf("%s: ",name);
//    getline(info);
//  }
//}



// 提示字段获取信息，及自定义字段
//void Command::multiInput() {
////  checkAndGetString("title", com.ai.title);
////  checkAndGetString("nickname", com.ai.nickname);
////  checkAndGetString("company", com.ai.company);
////  checkAndGetString("account", com.ai.account);
////  checkAndGetString("passwd", com.ai.passwd);
////
//
//}

bool Command::input() {
  std::cout << "# ";
  std::string s;
  _cmm.clear();
  bool isEnd = false;
  while(!isEnd && getline(std::cin, s)) {// 输入正常则返回true
    if (_cmm.empty()) {
      _cmm = s;
    }else {
      _cmm = _cmm + " " + s;
    }
    if (';' == s[s.length() - 1]) {
      isEnd = true;
    } else if(s.empty()) {
      std::cout << "# ";
    } else {
      std::cout << "> ";
    }
    s.clear();
  }
  if (!_cmm.empty()) {
    _cmm.erase(_cmm.length() - 1);
  }
  return true;
}

//struct command Command::cmd() {
//  return com;
//}

//bfzq::List<Field> Command::getCmd() {
//  return _field_list;
//}

uint8_t* Command::getSol() {
  return (uint8_t*)const_cast<char*>(_cmm.c_str());
//  return static_cast<uint8_t*>();
//  _cmm.c_str();
}

std::string Command::getCmm() {
  return _cmm;
}


void Command::setCommandStruct(bfzq::List<Field> field) {
  _field_list  = field;
}
