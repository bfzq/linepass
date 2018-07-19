//
//  main.cpp
//  index
//
//  Created by Saber on 2018/4/19.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "lineprogram.hpp"
//#include "secret.h"
int main(int argc, char * argv[]) {
      LineProgram* lp = new LineProgram() ;
      int retVal = lp->main(argc, argv) ;
      return retVal;
//string plainText = "This Program shows how to use ECB, CBC, CBC_CTS, CFB, OFB and CTR mode of AES in Crypto++.";
//    string aesKey = "0123456789ABCDEF0123456789ABCDEF";//256bits, also can be 128 bits or 192bits  
//    string aesIV = "ABCDEF0123456789";//128 bits  
//    string ECB_EncryptedText, ECB_DecryptedText,
//        CBC_EncryptedText, CBC_DecryptedText,
//        CBC_CTS_EncryptedText, CBC_CTS_DecryptedText,
//        CFB_EncryptedText, CFB_DecryptedText,
//        OFB_EncryptedText, OFB_DecryptedText,
//        CTR_EncryptedText, CTR_DecryptedText;
//
//    //ECB  
//    ECB_EncryptedText = ECB_AESEncryptStr(aesKey, plainText.c_str());//ECB加密  
//    ECB_DecryptedText = ECB_AESDecryptStr(aesKey, ECB_EncryptedText.c_str());//ECB解密  
//
//                                                                             //CBC  
//    CBC_EncryptedText = CBC_AESEncryptStr(aesKey, aesIV, plainText.c_str());//CBC加密  
//    CBC_DecryptedText = CBC_AESDecryptStr(aesKey, aesIV, CBC_EncryptedText.c_str());//CBC解密  
//
//                                                                                    //CBC_CTS  
//    CBC_CTS_EncryptedText = CBC_CTS_AESEncryptStr(aesKey, aesIV, plainText.c_str());//CBC_CTS加密  
//    CBC_CTS_DecryptedText = CBC_CTS_AESDecryptStr(aesKey, aesIV, CBC_CTS_EncryptedText.c_str());//CBC_CTS解密  
//
//                                                                                                //CFB  
//    CFB_EncryptedText = CFB_AESEncryptStr(aesKey, aesIV, plainText.c_str());//CFB加密  
//    CFB_DecryptedText = CFB_AESDecryptStr(aesKey, aesIV, CFB_EncryptedText.c_str());//CFB解密  
//
//                                                                                    //OFB  
//    OFB_EncryptedText = OFB_AESEncryptStr(aesKey, aesIV, plainText.c_str());//OFB加密  
//    OFB_DecryptedText = OFB_AESDecryptStr(aesKey, aesIV, OFB_EncryptedText.c_str());//OFB解密  
//
//                                                                                    //CTR  
//    CTR_EncryptedText = CTR_AESEncryptStr(aesKey, aesIV, plainText.c_str());//CTR加密  
//    CTR_DecryptedText = CTR_AESDecryptStr(aesKey, aesIV, CTR_EncryptedText.c_str());//CTR解密  
//
//    cout << "Crypto++ AES-256 加密测试" << endl;
//    cout << "分别使用ECB，CBC, CBC_CTR，CFB，OFB和CTR模式" << endl;
//    cout << "加密用密钥:" << aesKey << endl;
//    cout << "密钥长度:" << AES::MAX_KEYLENGTH * 8 << "bits" << endl;
//    cout << "IV:" << aesIV << endl;
//    cout << endl;
//
//    cout << "ECB测试" << endl;
//    cout << "原文：" << plainText << endl;
//    cout << "密文：" << ECB_EncryptedText << endl;
//    cout << "恢复明文：" << ECB_DecryptedText << endl << endl;
//
//    cout << "CBC测试" << endl;
//    cout << "原文：" << plainText << endl;
//    cout << "密文：" << CBC_EncryptedText << endl;
//    cout << "恢复明文：" << CBC_DecryptedText << endl << endl;
//
//    cout << "CBC_CTS测试" << endl;
//    cout << "原文：" << plainText << endl;
//    cout << "密文：" << CBC_CTS_EncryptedText << endl;
//    cout << "恢复明文：" << CBC_CTS_DecryptedText << endl << endl;
//
//    cout << "CFB测试" << endl;
//    cout << "原文：" << plainText << endl;
//    cout << "密文：" << CFB_EncryptedText << endl;
//    cout << "恢复明文：" << CFB_DecryptedText << endl << endl;
//
//    cout << "OFB测试" << endl;
//    cout << "原文：" << plainText << endl;
//    cout << "密文：" << OFB_EncryptedText << endl;
//    cout << "恢复明文：" << OFB_DecryptedText << endl << endl;
//
//    cout << "CTR测试" << endl;
//    cout << "原文：" << plainText << endl;
//    cout << "密文：" << CTR_EncryptedText << endl;
//    cout << "恢复明文：" << CTR_DecryptedText << endl << endl;
//
//        return 0;
}
