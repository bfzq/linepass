//
//  struct.h
//  LinePassword
//
//  Created by 猪摇摇 on 2018/6/8.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef struct_h
#define struct_h
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <ctime>
#include "list.hpp"
#include <json/json.h>
#include "netstruct.hpp"

#define CALLBACKOK "ok"
#define CALLBACKERR "err"


#define TITLESIZE 64
#define COMPANYSIZE 128
#define ACCOUNTSIZE 256
#define PASSWDSIZE 256
#define NICKNAMESIZE 64
#define CONTENTSIZE 256
//#define LOGIN 0
//#define COMMAND 1




// 用户信息
struct user_config {
  int user_id;
  char user_user[256];
  char user_password[256];
};

// 帐号信息
struct accountinfo {
  char title[TITLESIZE] = {'\0'};
  char company[COMPANYSIZE]  = {'\0'};
  char account[ACCOUNTSIZE]  = {'\0'};
  char passwd[PASSWDSIZE]  = {'\0'};
  char nickname[NICKNAMESIZE]  = {'\0'};
  void empty() {
    title[0] = '\0';
    company[0] = '\0';
    account[0] = '\0';
    passwd[0] = '\0';
    nickname[0] = '\0';
  }
};


#define FIELDNAMESIZE 256
#define VALUESIZE 256
// 字段信息
struct Field {
  std::string fieldName;
  std::string value;
  bool secret; // 是否加密
  
  Field() = default;
  Field(const Field& f) {
    fieldName = f.fieldName;
    value = f.value;
    secret = f.secret;
  }
  
  //判断字段是否需要加密
  bool isSecret(const char* word) {
    if (strlen(word) > 3 && word[0] == '*' && word[1] == '"' && word[strlen(word) - 1] == '"') {
      return true;
    }
    return false;
  }
  
  Field(std::string f, std::string v, bool s) : fieldName(f), value(v), secret(s) {}
  
  Field(std::string s, std::string is) { // is:隔离符号
    std::string::size_type mdx = s.find_first_of(is, 0); // 切割位置
    fieldName = s.substr(0, mdx);
    std::string v = s.substr(mdx + 1);
    secret = isSecret(v.c_str()); // 判断是否加密
    if (secret) {
      v.erase(0, 2);
      v.erase(v.size() - 1);
    }
    value = v;
  }
  
  bool operator=(const Field& field) {
    if (fieldName == field.fieldName && value == field.value) {
      return true;
    } else {
      return false;
    }
  }
};


struct Account {
  unsigned int aid;
  bfzq::List<Field> list;
  Account() = default;
  Account(const Account& a) {
    aid = a.aid;
    list = a.list;
  }
};

struct dbdata {
  unsigned int aid;
  std::string fieldName;
  std::string value;
  bool secret; // 是否加密
  dbdata(unsigned int a, std::string f, std::string v, bool s) : aid(a), fieldName(f), value(v), secret(s) {}
};


enum type: uint16_t {show,put,edit,del,search,quit,result, ty_zero}; // 命令模式
enum subtype: uint16_t {all,tittle,company,account,nickname,sub_zero};
const char type_s[7][7] = {"show","put","edit","del","search","quit","result"};
const char subtype_s[5][9] = {"all","title","company","account","nickname"};

/*
 *  show title:第一个标题
 *  search nickname:小红
 *  put account:adasd passwd:asdasd
 *  del no:1
 */
struct command {
  enum type cmd; // 命令模式
  bfzq::List<Field> list;
  
  bool assemble(std::string jsonstr) {
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(jsonstr, root)) {
      cmd = (enum type)root[0].asUInt();
      list = json_to_struct<Field,bfzq::List>(root[1].toStyledString(), [](bfzq::List<Field>& list, Json::Value value) {
        
      });
      return true;
    } else {
      return false;
    }
    
  }
  
  void empty() {
    cmd = type::ty_zero;
    list.clean();
  }
  bool gettype(const char* ty) {
    ushort i;
    for(i = 0; i < 7; i++) {
      if(0 == strcmp(type_s[i], ty)) {
        cmd = (enum type)i;
        return true;
        break;
      }
    }
    if (i == 6) cmd = type::ty_zero;
    return false;
  }
};








#endif /* struct_h */
