#include <aes.h>  
#include <hex.h>      // StreamTransformationFilter  
#include <modes.h>    // CFB_Mode  
#include <iostream>   // std:cerr    
#include <sstream>   // std::stringstream    
#include <string>  

using namespace std;
using namespace CryptoPP;
// #pragma comment(lib, "cryptlib.lib" )  

std::string ECB_AESEncryptStr(std::string sKey, const char *plainText, size_t len);
std::string ECB_AESDecryptStr(std::string sKey, const char *cipherText);

std::string CBC_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText);
std::string CBC_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText);

std::string CBC_CTS_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText);
std::string CBC_CTS_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText);

std::string CFB_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText);
std::string CFB_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText);

std::string OFB_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText);
std::string OFB_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText);

std::string CTR_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText);
std::string CTR_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText);
