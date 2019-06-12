//
//  linesecret.hpp
//  LinePassword
//
//  Created by Saber on 2018/4/27.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef linesecret_hpp
#define linesecret_hpp
#include <iostream>
#include <cryptopp/aes.h>
#include <string>
#include <map>
#include <string.h>


using namespace CryptoPP;

class LineSecret 
{
private:
  unsigned char k[AES::DEFAULT_KEYLENGTH]; // 密钥
  unsigned char xorblock[AES::BLOCKSIZE];
  AESEncryption* aesencrypt; // 加密器
  AESDecryption* aesdecryptor; // 解密器
public:
  LineSecret();
  ~LineSecret();
public:
  bool setKey(const unsigned char key[AES::DEFAULT_KEYLENGTH]); // 密钥
//  bool setData(unsigned char data[AES::BLOCKSIZE]); // 加密数据块
  unsigned char* encrypt(const unsigned char plainText[AES::BLOCKSIZE]); // aes加密
  unsigned char* decipher(const unsigned char keyText[AES::BLOCKSIZE]); // 解密
};

#endif /* linesecret_hpp */
