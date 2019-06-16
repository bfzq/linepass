//
//  lineprogram.hpp
//  LinePassword
//
//  Created by Saber on 2018/4/23.
//  Copyright © 2018 Saber. All rights reserved.
//

#ifndef lineprogram_hpp
#define lineprogram_hpp
#include "mainprogram.hpp"
#include "linesecret.hpp"
#include "link.hpp"
#include "mysqlc.h"
#include <unistd.h>
#include "comline.hpp"
#include "struct.h"
#include "mysqlcpool.hpp"
#include "secret.h"
#include "const.h"
#include <stdlib.h>
#include "granalysis.hpp"
#include "netstruct.hpp"



#define LISTENPORT "listen-port"
#define POOLNUM "pool-num"


extern const unsigned char* LINETESTKEY;



struct server_config
{
  int listen_port;
  uint16_t poolnum;
  server_config() {};
  server_config(std::map<std::string, std::string>*);
  void init(std::map<std::string, std::string>*);
};

class LineProgram : public MainProgram {
private:
  struct server_config sc; // 
  LineSecret* ls; // 
  LineLink* link; // 
    MysqlcPool* mp; // my
  struct mysql_config mc; // mysql 
  Granalysis granalysis; // 
public:
  LineProgram();
  ~LineProgram();
public:
  int main(int argc, char* argv[]);
  int main();
private:
  void initMysqlPool();
  bool intoDameon(); //
  void tasks();
  void initParameter(int argc, char* argv[]);
  void getServerPara();
//  bool certify(int);
  bool certify(struct user_config*, uint8_t*);
  // 
  void feedBack(int client_socket, Server server , const char* unsafedata, size_t datasize);
//  void hideArg(int argc, char** argv, const char* arg);
private:
  void commandWork(struct user_config* uc, int client_socket, uint8_t* cmd);
private:
  void showUserAccount(struct command comma, struct user_config* uc, int client_socket); // 
  void putAccountToServer(struct command comma, struct user_config* uc, int client_socket); // 
  void editAccount(struct command comma, struct user_config* uc, int client_socket); // 
  void delAccount(struct command comma, struct user_config* uc, int client_socket); // 
};

#endif /* lineprogram_hpp */
