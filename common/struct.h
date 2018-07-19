//
//  struct.h
//  LinePassword
//
//  Created by 猪摇摇 on 2018/6/8.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef struct_h
#define struct_h
#include <string>
#include <ctime>

#define CALLBACKOK "ok"

//#define LOGIN 0
//#define COMMAND 1

struct user_config {
	char user_user[256];
	char user_password[256];
};


struct communication_test {
	char app_name[64] ; // application name
	char account[128] ; // account
	char password[128] ; // password
	time_t create_time ; // create time that accout is created
	char nick_name[64] ; // nick name
	int fk_login_sequence_id ; // id of a sequence to login
};


struct sys_info {
	unsigned int idx ;  // page idx
	unsigned int pages ; // num of pages ;
	struct communication_test ct ; // one account info
};






#endif /* struct_h */
