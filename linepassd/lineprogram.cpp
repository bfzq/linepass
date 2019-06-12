//  lineprogram.cpp
//  LinePassword
//
//  Created by Saber on 2018/4/23.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "lineprogram.hpp"

server_config::server_config(std::map<std::string, std::string>* m) {
  init(m);
  
}

void server_config::init(std::map<std::string, std::string> * m) {
  listen_port = atoi((*m)[LISTENPORT].c_str());
  poolnum = atoi((*m)[POOLNUM].c_str());
}



LineProgram::LineProgram() {
  ls = new LineSecret();
  link = new LineLink(LineLink::SERVER);
  mp = new MysqlcPool();
}


LineProgram::~LineProgram() {
  delete ls;
  delete link;
  delete mp;
}

int LineProgram::main(int argc, char **argv) {
    __mysql_library_init__
  initParameter(argc, argv);
  if (cl->haveHelp()) {
    cl->printHelpInfo();
    return 0;
  }
  // intoDameon(); // DEBUG期间关闭
  getServerPara();
  initMysqlPool();
  hideArg(argc,argv,"mysql-passwd"); // 隐藏密码
  tasks();
    __mysql_library_end__
  return 0;
}


/*
 *    初始化mysql连接池
 */
void LineProgram::initMysqlPool() {
  mp->init(mc, sc.poolnum);
}


void LineProgram::getServerPara() {
  sc.init(cl->map);
  mc.init(cl->map);
}


void LineProgram::initParameter(int argc, char **argv) {
  cl->getKeyValue(argc, argv);
}


bool LineProgram::certify(struct user_config* uc, uint8_t* buf) {
  bool retVal = false;
  memcpy(uc, buf, sizeof(user_config));
  Mysqlc* local_mysql = mp->getMysqlCon();
  std::string sql = "select id,password from users where username='" + std::string((*uc).user_user) + "' limit 1";
  local_mysql->query(sql.c_str(), [&retVal,&uc](MYSQL_ROW row) {
    if (strcmp((*uc).user_password, ECB_AESDecryptStr(aesDbKey,row[1]).c_str()) == 0) {
      (*uc).user_id = atoi(row[0]);
      retVal = true;
    }else {
      retVal = false;
    }
    return true;
  }, [&retVal]() {
    retVal = false;
  });
  mp->backMysqlCon(local_mysql);
  local_mysql = nullptr;
  return retVal;
}


void LineProgram::commandWork(struct user_config* uc, int client_socket,uint8_t *cmdStr) {
  if (!granalysis.morphology((const char*)cmdStr)) {
    // <#语法解析错误处理部分#>
  }
  struct command cmd = granalysis.getStructCmd();
  switch (cmd.cmd) {
    case type::put:{
      putAccountToServer(cmd, uc, client_socket);
      break;
    }
    case type::show:{
      showUserAccount(cmd, uc, client_socket);
      break;
    }
        case type::edit:{
      editAccount(cmd, uc, client_socket);
      break;
    }
    case type::del:
    {
      delAccount(cmd, uc, client_socket);
      break;
    }
    default:
      break;
  }
  
}


void LineProgram::tasks() {
  link->listenPort(sc.listen_port);
  link->init();
  link->serverListen();
  link->serverAccpet([&](int client_socket) {
    struct user_config uc;
    /*
     * 交互
     */
    uint32_t byte = 0; // 返回长度
    uint8_t buf[PROTO_HEAD_SIZE]; // 缓存
    while ((byte = recv(client_socket, buf, PROTO_HEAD_SIZE, 0)) > 0) { // 获取到客户端的数据 buf
      struct proto_head ph; // 数据包头
      if(!link->parser(buf, byte, &ph)) continue;
      if (ph.len > PROTO_HEAD_SIZE) {  // 检查数据体长度是否合法
        // 获取数据体
        uint32_t datalen = ph.len - PROTO_HEAD_SIZE;
        int8_t* data = (int8_t*)malloc(sizeof(int8_t) * (datalen + 1));
        if ((byte = recv(client_socket, data, datalen, 0)) <= 0) {
          free(data);
          continue;
        }
        data[datalen] = '\0';
        
        /*
         *  解密数据体
         */
        uint8_t* unsafeData = (uint8_t*)ECB_AESDecryptStr(aesKey,(const char*)data).c_str();
        
        switch (ph.server) {
            // 登录验证
          case LOGIN:{ // error:Cannot jump from switch statement to this case label \
            # 因为switch case 中是不能定义对象的，因为只要是在大括号内定义的对象。\
            所以只需要在case:后面加上大括号就OK.
            
            // 记录返回报文
            std::string backtext;
            // 验证数据包
            if(certify(&uc, unsafeData)) {
              // 验证成功，返回ok
              backtext = CALLBACKOK;
            }else {
              // 验证失败，返回err
              backtext = CALLBACKERR;
            }
            
            /*
             * 返回客户信息
             */
            this->feedBack(client_socket, LOGIN, backtext.c_str(), backtext.size());
            break;
          }
          case COMMAND:
            // 处理命令信息
            commandWork(&uc,client_socket,unsafeData);
            break;
          default:
            break;
        }
        free(data);
      }
    }
    close(client_socket);
  });
}


int LineProgram::main() {
  intoDameon(); // xcode 编辑期间关闭
  return 0;
}


bool LineProgram::intoDameon() {
  pid_t pc;
  pc = fork(); /*第一步:创建子进程*/
  if(pc<0){
    return false;
  }else if(pc>0){//父进程退出
    exit(0);
  }
  if(setsid() < 0) {
    return false;
  } else {
    return true;
  }/*第二步:在子进程中创建新会话*/
}

void LineProgram::putAccountToServer(struct command comma, struct user_config *uc, int client_socket) {
  Mysqlc* local_mysql = mp->getMysqlCon();
  try {
    local_mysql->begin();
    
    //拼装添加帐号语句
    std::string insert_accounts = "insert into accounts(usersid,field_numbers) value("
    + std::to_string(uc->user_id) + "," + std::to_string(comma.list.size()) + ")";
    local_mysql->execute(insert_accounts.c_str(),nullptr);
    
    // 拼装帐号详情语句
    std::string insert_sql = "insert into field_list(accountsid,field,value,secert) values";
    comma.list.foreach([&insert_sql](Field field) {
      std::string secretstr;
      if (field.secret) {
        secretstr = ECB_AESEncryptStr(aesDbKey, field.value.c_str(), field.value.size());
      } else {
        secretstr = field.value;
      }
      insert_sql = insert_sql + "(last_insert_id(),'"
      + field.fieldName + "','" + secretstr + "'," + std::to_string(field.secret) + "),";
    });
    
    
    insert_sql.erase(insert_sql.length() - 1);
    
    //execute insert_sql
    local_mysql->execute(insert_sql.c_str(),nullptr);
    local_mysql->commit();
    
    /*
     * 返回客户信息, ok
     */
    std::string backinfo = "the put is success.";
    feedBack(client_socket, MESSAGE, backinfo.c_str(), backinfo.size());
  } catch (MysqlcException &me) {
    me.what();
    local_mysql->rollback();
    /*
     * 返回客户信息, err
     */
    std::string backinfo = "the put is error.";
    feedBack(client_socket, MESSAGE, backinfo.c_str(), backinfo.size());
  }
  mp->backMysqlCon(local_mysql);
  local_mysql = nullptr;
}


void LineProgram::showUserAccount(struct command comma, struct user_config* uc, int client_socket) {
  Mysqlc* local_mysql = mp->getMysqlCon();
  try {
    
    bfzq::List<dbdata> tmpResult;
    bfzq::List<Account> result;
    
//     查询用户账户SQL语句
    std::string select_sql = "select accountsid,field,value,secert from `field_list` where accountsid in (select distinct f.`accountsid` from `accounts` as a left join `field_list` as f on a.`id` = f.`accountsid` where a.`usersid` = " + std::to_string(uc->user_id) + " and ";
    comma.list.foreach([&select_sql](Field field) {
      if (field.fieldName == "f") {
        select_sql = select_sql + " f.`field` like '%" + field.value + "%' or ";
      } else if (field.fieldName == "v") {
        select_sql = select_sql + " f.`value` like '%" + field.value + "%' or ";
      }
    });
    select_sql.erase(select_sql.length() - 4);
    select_sql = select_sql + ") order by accountsid";
    
    // 查询数据，并缓存..
    int mark = -1; // 标记帐号
    local_mysql->query(select_sql.c_str(), [&tmpResult, &result, &mark] (MYSQL_ROW row){
      int id = 0;
      std::string f,v;
      bool s = false;
      (NULL != row[3])? s = atoi(row[3]) : false;
      (NULL != row[0])? id = atoi(row[0]) : 0;
      (NULL != row[1])? f = row[1] : nullptr;
      if (s) {
        (NULL != row[2])? v = ECB_AESDecryptStr(aesDbKey, row[2]) : nullptr;
      } else {
        (NULL != row[2])? v = row[2] : nullptr;
      }
      
      
      if (mark == -1) mark = id;
    reput:
      if (id == mark) {
        tmpResult.Insert(dbdata(id, f, v, s));
      } else {
        Account a;
        tmpResult.foreach([&a](dbdata data) {
          a.aid = data.aid;
          a.list.Insert(Field(data.fieldName, data.value, data.secret));
        });
        result.Insert(a);
        mark = id;
        tmpResult.clean();
        goto reput;
      }
      return true;
    }, nullptr);

    if (!tmpResult.isEmpty()) {
      Account a;
      tmpResult.foreach([&a](dbdata data) {
        a.aid = data.aid;
        a.list.Insert(Field(data.fieldName, data.value, data.secret));
      });
      result.Insert(a);
    }
    // ..查询数据，并缓存
    
    // 数据json化
    Json::Value json;
    result.foreach([&json](Account account) {
      
      Json::Value item = struct_to_json_struct<Field,bfzq::List>(account.list,[](std::vector<std::string>& item, Field f){
        item.push_back(f.fieldName);
        item.push_back(f.value);
        item.push_back(f.secret? "1" : "0");
      });
      
      json[std::to_string(account.aid)] = item;
    });
    
    /*
     * 返回客户账户数据结束
     */
    std::string jsonstr = json.toStyledString();
    feedBack(client_socket, RESULT, jsonstr.c_str(), jsonstr.size());
  
  } catch(MysqlcException &me) {
    me.what();
    feedBack(client_socket, MESSAGE, "error", strlen("error"));
  }
  feedBack(client_socket, DONE, "", 0);
  mp->backMysqlCon(local_mysql);
  local_mysql = nullptr;
}

void LineProgram::editAccount(struct command comma, struct user_config* uc, int client_socket) 
{
    Mysqlc* local_mysql = mp->getMysqlCon();
    try {
    /* get zhe account id and delete id from list. */
    std::string account_id = comma.list[0].value;
    comma.list.Delete(0);

    
      local_mysql->begin();
    comma.list.foreach([&account_id, &local_mysql] (Field field) {
         std::string secretstr;
        if (field.secret)
      {
        secretstr = ECB_AESEncryptStr(aesDbKey, field.value.c_str(), field.value.size());
         } else
        {
         secretstr = field.value;
      }
        std::string sql_update = "update field_list set value='" + secretstr 
        + "',secert=" + std::to_string(field.secret) + " where accountsid = " + account_id 
        + " and field = '" + field.fieldName + "'";  
        bool haveData = false;
        /*update field.*/
        local_mysql->execute(sql_update.c_str(), [&haveData](long affected_rows){
              if (affected_rows) 
              {
                haveData = true;
              }
            });
        if (!haveData) 
        {  /*if there isn't field , add it*/
          std::string sql_insert = "insert into field_list(accountsid,field,value,secert) value(" 
            + account_id +",'"+ field.fieldName +"','"+ secretstr +"',"+ std::to_string(field.secret) +")";
          local_mysql->execute(sql_insert.c_str(), nullptr);
        }
      });
    local_mysql->commit();
    /*
                 * 返回客户信息, ok
                 */
                std::string backinfo = "the edit is success.";
                feedBack(client_socket, MESSAGE, backinfo.c_str(), backinfo.size());
    } catch (MysqlcException& me) {
        local_mysql->rollback();
    /*
                 * 返回客户信息, err
                 */
                std::string backinfo = "the edit is error.";
                feedBack(client_socket, MESSAGE, backinfo.c_str(), backinfo.size());
    }
  mp->backMysqlCon(local_mysql);
  local_mysql = nullptr;
}

void LineProgram::delAccount(struct command comma, struct user_config* uc, int client_socket) 
{
  /*get a mysql connection*/
  Mysqlc* local_mysql = mp->getMysqlCon();
  std::string accountid = comma.list[0].value;
  comma.list.Delete(0);
  try {
    std::string sql_delete = "delete from field_list where accountsid = " +  accountid;
    comma.list.foreach([&sql_delete] (Field field) {
      static bool mark = false;
      if (mark) {
        sql_delete = sql_delete + " or field = '" + field.fieldName + "'";
      } else {
        sql_delete = sql_delete + " and field = '" + field.fieldName + "'";
        mark = true;
      }
    });
    std::string sql_delete_2 = "delete from accounts where id = "+ accountid +" and not exists (select 1 from field_list where accountsid = "+ accountid +");";

    local_mysql->begin();
    local_mysql->execute(sql_delete.c_str(), nullptr);
    local_mysql->execute(sql_delete_2.c_str(), nullptr);
    local_mysql->commit();
    std::string binfo = "delete success.";
    feedBack(client_socket, MESSAGE ,binfo.c_str(), binfo.size());
  } catch (MysqlcException& me) {
    local_mysql->rollback();
    std::string binfo = "delete error.";
    feedBack(client_socket, MESSAGE, binfo.c_str(), binfo.size());
  }
  mp->backMysqlCon(local_mysql);
//    delete local_mysql;
  local_mysql = nullptr;
}


// 返回数据
void LineProgram::feedBack(int client_socket, Server server, const char* unsafedata, size_t datasize) {
  std::string safedata = ECB_AESEncryptStr(aesKey, unsafedata, datasize);
  struct proto_msg mg(server, (uint8_t*)safedata.c_str(), safedata.size());
  
  uint32_t len; // 网络报文长度
  uint8_t* pdata = link->encode(mg, len);
  std::cout << len << std::endl;
  
  send(client_socket, pdata, len, 0);
}
