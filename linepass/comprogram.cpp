//
//  comprogram.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/5/14.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "comprogram.hpp"

void print_list(bfzq::List<Account> accounts) 
{
  accounts.foreach([](Account account) {
  printf("%u :\n",account.aid);
    account.list.foreach([](Field field) {
      printf("  %s : %s  #secret:%d\n",field.fieldName.c_str(),field.value.c_str(),field.secret);
    });
  });
}

client_config::client_config(std::map<std::string, std::string>* m) {
  init(m);
}

void client_config::init(std::map<std::string, std::string> * m) {
  connect_host = (*m)[CONNECTHOST];
  connect_port = atoi((*m)[CONNECTPORT].c_str());
  connect_user = (*m)[CONNECTUSER];
  connect_password = (*m)[CONNECTPASSWORD];
}

ComProgram::ComProgram() {
  link = new LineLink(LineLink::CLIENT);
  cmd = new Command();
  ls = new LineSecret();
  //  lc = new ComLine();
}

ComProgram::~ComProgram() {
  delete link;
  delete cmd;
  delete ls;
  ls = nullptr;
  cmd = nullptr;
  link = nullptr;
}


bool ComProgram::connectServer() {
  /*
   *  设置连接端口和ip
   */
  link->clientPort(cc.connect_port);
  link->clientHost(cc.connect_host);
  
  
  if(!link->init()) return false;
  return link->clientConnect();
  return true;
}

bool ComProgram::interactive() {
  while (true) {
    if (cmd->input()) {
      if (cmd->getCmm() == _SLASH_Q_ || cmd->getCmm() == _QUIT_
        || cmd->getCmm() == _EXIT_) { // 主动退出
        return false;
      } else {
        // 数据装配
        std::string safedata = ECB_AESEncryptStr(aesKey, cmd->getCmm().c_str(), cmd->getCmm().length());
        struct proto_msg mg(COMMAND, (uint8_t*)safedata.c_str(), safedata.length());
        uint32_t len = 0;
        uint8_t* pData = NULL;
        pData = link->encode(mg, len);
        // 发送数据
        if(link->clientSend(pData, len)) {
          Server type;
          unsigned int num = 0; // 返回结果数
          unsigned revcStatus =  0; // 正常查询结果
          do {
                        
            link->clientRevc([&revcStatus,&type, this](struct proto_msg pm){
              type = pm.server;
              switch(pm.server) {
                case Server::MESSAGE: {
                  std::string back_str = ECB_AESDecryptStr(aesKey, (const char*)pm.data);
                  printf("---\n");
                  printf("message: %s\n",back_str.c_str());
                  revcStatus = 1;
                  break;
                }
                case Server::RESULT: {
                  // 数据解密
                  std::string data = ECB_AESDecryptStr(aesKey, (const char*)pm.data);
                  // 数据打包进数据结构
                  bfzq::List<Account> accounts = json_to_struct<Account,bfzq::List>(data, [](Json::Value::Members::iterator iter, std::string json) {
                    Account account;
                    account.aid = atoi((*iter).c_str());
                    
                    account.list = json_to_struct<Field, bfzq::List>(json, [](bfzq::List<Field>& list, Json::Value value){
                      list.Insert(Field(value[0].asString(), value[1].asString(), value[2].asString() == "1"? true : false));
                    });
                    return account;
                  });
                  
                  print_list(accounts);
                  
                  
                  
                  revcStatus = 2;
                  break;
                }
                default:{
                  break;
                }
              }
              return true;
            });
          } while(Server::RESULT == type);
        }
      }
    }
  }
}




int ComProgram::main(int argc, char **argv) {
  
  
  cl->getKeyValue(argc, argv);
  cc.init(cl->map);
  hideArg(argc,argv,"line-passwd"); // 隐藏密码
  
  /*
   * 连接服务器，失败退出
   */
  if (!connectServer()) {
    log("err: can not connect linepassd server.");
    return 1;
  }
  
  /*
   * 信息认证
   */
  if(!certify(link)) {
    link->linkClose();
    log("err: certify.");
    return 1;
  }
  
  
  if (!interactive()) {
    link->linkClose();
    return 0;
  }
  return 0;
}

bool ComProgram::certify(LineLink* lk) {
  /*
   *  转移用户信息
   */
  struct user_config uc; // struct.h
  
  // 把用户信息复制到uc
  strcpy(uc.user_user, cc.connect_user.c_str());
  strcpy(uc.user_password, cc.connect_password.c_str());
  
  size_t size = sizeof(uc);
  char* plain = (char*)malloc(sizeof(char) * size);
  memcpy(plain,(char*)&uc,size);
  
  
  
  
  std::string data = ECB_AESEncryptStr(aesKey,plain,size);
  struct proto_msg pm(LOGIN, (uint8_t*)data.c_str(), data.length());
  uint32_t package_size;
  uint8_t* pdata = link->encode(pm, package_size);
  
  /*
   *  发送登录验证信息
   */
  if(!lk->clientSend(pdata, package_size)) {
    return false;
  }
  
  /*
   *  返回报文
   */
  bool retVal = false;
  lk->clientRevc([&](struct proto_msg pm) {
    try {
      if (LOGIN == pm.server) {
        const char* tmp_str = ECB_AESDecryptStr(aesKey, (const char*)pm.data).c_str();
        if (!strcmp(tmp_str, CALLBACKOK)) {
          retVal = true;
        }
      }
    } catch (Exception &e) {
      printf("err: %s\n",e.what());
    }
  });
  return retVal;
}

int ComProgram::main() {
  return 0;
}
