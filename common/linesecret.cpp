//
//  linesecret.cpp
//  LinePassword
//
//  Created by Saber on 2018/4/27.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include "linesecret.hpp"

const unsigned char* LINETESTKEY = (unsigned char*)"12345678901234561" ;

LineSecret::LineSecret() {
	aesencrypt = new CryptoPP::AESEncryption() ; // 加密器
	aesdecryptor = new CryptoPP::AESDecryption() ; // 解密器
}



LineSecret::~LineSecret() {
	delete aesencrypt ;
	aesencrypt = nullptr ;
	delete aesdecryptor ;
	aesdecryptor = nullptr ;
}

bool LineSecret::setKey(const unsigned char *key) {
	memset(xorblock, 0, AES::BLOCKSIZE ); //置零
	memcpy(k, key, AES::DEFAULT_KEYLENGTH) ;
	return true ;
}


unsigned char* LineSecret::encrypt(const unsigned char *plainText) {
	static unsigned char outBlock[AES::BLOCKSIZE]; // 加密后密码块
	aesencrypt->SetKey(k, AES::DEFAULT_KEYLENGTH) ;
	aesencrypt->ProcessAndXorBlock(plainText, xorblock, outBlock) ;
	return outBlock;
}

unsigned char* LineSecret::decipher(const unsigned char *keyText) {
	static unsigned char outBlock[AES::BLOCKSIZE]; // 解密后密码块
	aesdecryptor->SetKey(k, AES::DEFAULT_KEYLENGTH) ;
	aesdecryptor->ProcessAndXorBlock(keyText, xorblock, outBlock) ;
	return outBlock;
}
