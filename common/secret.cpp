#include "secret.h"


std::string ECB_AESEncryptStr(std::string sKey, const char *plainText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);


    AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

    ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);
    StreamTransformationFilter ecbEncryptor(ecbEncryption, new HexEncoder(new StringSink(outstr)));
    ecbEncryptor.Put((byte *)plainText, strlen(plainText));
    ecbEncryptor.MessageEnd();

    return outstr;
}

std::string ECB_AESDecryptStr(std::string sKey, const char *cipherText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    ECB_Mode<AES >::Decryption ecbDecryption((byte *)key, AES::MAX_KEYLENGTH);

    HexDecoder decryptor(new StreamTransformationFilter(ecbDecryption, new StringSink(outstr)));
    decryptor.Put((byte *)cipherText, strlen(cipherText));
    decryptor.MessageEnd();

    return outstr;
}

std::string CBC_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);

    AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

    CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

    StreamTransformationFilter cbcEncryptor(cbcEncryption, new HexEncoder(new StringSink(outstr)));
    cbcEncryptor.Put((byte *)plainText, strlen(plainText));
    cbcEncryptor.MessageEnd();

    return outstr;
}

std::string CBC_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);


    CBC_Mode<AES >::Decryption cbcDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);

    HexDecoder decryptor(new StreamTransformationFilter(cbcDecryption, new StringSink(outstr)));
    decryptor.Put((byte *)cipherText, strlen(cipherText));
    decryptor.MessageEnd();

    return outstr;
}

std::string CBC_CTS_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);

    AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

    CBC_CTS_Mode_ExternalCipher::Encryption cbcctsEncryption(aesEncryption, iv);

    StreamTransformationFilter cbcctsEncryptor(cbcctsEncryption, new HexEncoder(new StringSink(outstr)));
    cbcctsEncryptor.Put((byte *)plainText, strlen(plainText));
    cbcctsEncryptor.MessageEnd();

    return outstr;
}

std::string CBC_CTS_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);


    CBC_CTS_Mode<AES >::Decryption cbcctsDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);

    HexDecoder decryptor(new StreamTransformationFilter(cbcctsDecryption, new StringSink(outstr)));
    decryptor.Put((byte *)cipherText, strlen(cipherText));
    decryptor.MessageEnd();

    return outstr;
}

std::string CFB_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);

    AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

    CFB_Mode_ExternalCipher::Encryption cfbEncryption(aesEncryption, iv);

    StreamTransformationFilter cfbEncryptor(cfbEncryption, new HexEncoder(new StringSink(outstr)));
    cfbEncryptor.Put((byte *)plainText, strlen(plainText));
    cfbEncryptor.MessageEnd();

    return outstr;
}

std::string CFB_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);


    CFB_Mode<AES >::Decryption cfbDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);

    HexDecoder decryptor(new StreamTransformationFilter(cfbDecryption, new StringSink(outstr)));
    decryptor.Put((byte *)cipherText, strlen(cipherText));
    decryptor.MessageEnd();

    return outstr;
}

std::string OFB_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);

    AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

    OFB_Mode_ExternalCipher::Encryption ofbEncryption(aesEncryption, iv);

    StreamTransformationFilter ofbEncryptor(ofbEncryption, new HexEncoder(new StringSink(outstr)));
    ofbEncryptor.Put((byte *)plainText, strlen(plainText));
    ofbEncryptor.MessageEnd();

    return outstr;
}

std::string OFB_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);


    OFB_Mode<AES >::Decryption ofbDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);

    HexDecoder decryptor(new StreamTransformationFilter(ofbDecryption, new StringSink(outstr)));
    decryptor.Put((byte *)cipherText, strlen(cipherText));
    decryptor.MessageEnd();

    return outstr;
}

std::string CTR_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);

    AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

    CTR_Mode_ExternalCipher::Encryption ctrEncryption(aesEncryption, iv);

    StreamTransformationFilter ctrEncryptor(ctrEncryption, new HexEncoder(new StringSink(outstr)));
    ctrEncryptor.Put((byte *)plainText, strlen(plainText));
    ctrEncryptor.MessageEnd();

    return outstr;
}

std::string CTR_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText)
{
    std::string outstr;

    //填key    
    SecByteBlock key(AES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

    //填iv    
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x30, AES::BLOCKSIZE);
    sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);


    CTR_Mode<AES >::Decryption ctrDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);

    HexDecoder decryptor(new StreamTransformationFilter(ctrDecryption, new StringSink(outstr)));
    decryptor.Put((byte *)cipherText, strlen(cipherText));
    decryptor.MessageEnd();

    return outstr;
}
