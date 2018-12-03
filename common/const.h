//
//  const.h
//  linepasswordindex
//
//  Created by Double on 2018/6/22.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef const_h
#define const_h
#include <string>
//
const std::string aesDbKey = "0123456789ABCDEF0123456789ABCDEF";//256bits, also can be 128 bits or 192bits. 数据库密码加密
const std::string aesKey = "5123456789ABCAEF0123456789ABCDEF";//256bits, also can be 128 bits or 192bits. 网络传输
const std::string aesIV = "ABCDEF0123456789";//128 bits

#endif /* const_h */
