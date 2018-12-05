//
//  main.cpp
//  linepasswordindex
//
//  Created by Saber on 2018/4/27.
//  Copyright © 2018年 Saber. All rights reserved.
//

#include <iostream>
#include "comprogram.hpp"


//#include "command.hpp"
//#include "list.hpp"
//#include "struct.h"
//#include "netstruct.hpp"
//#include <json/json.h>
//#include <vector>
//#include "secret.h"

int main(int argc,char* argv[]) {
	
//	uint8_t* s = (uint8_t*)malloc(sizeof(uint8_t) * sizeof("76FEE7636CBA86ABA7D4AF1ACE20FE834123456789ABCAEF0123456789ABCDEF")) ;
//	memcpy(s, "76FEE7636CBA86ABA7D4AF1ACE20FE834123456789ABCAEF0123456789ABCDEF", sizeof("76FEE7636CBA86ABA7D4AF1ACE20FE834123456789ABCAEF0123456789ABCDEF")) ;
//	std::cout << ECB_AESDecryptStr(aesKey, (const char*)s) << std::endl ;
	ComProgram *cp = new ComProgram() ;
	int retVal = cp->main(argc, argv) ;
	delete cp ;
	cp = nullptr ;
	return retVal ;
//	bfzq::List<Field> list ;
//	list.Insert(Field("asd", "zx\",\"c", false)) ;
//	list.Insert(Field("qwe", "ccz", true)) ;
	
//	uint8_t[] tmp = struct_to_uint8_t<bfzq::List,Field>(list, [](Field f){
//		uint8_t field[FIELDNAMESIZE + VALUESIZE], value[VALUESIZE] ;
//		memcpy(field, f.fieldName.c_str(), f.fieldName.size()) ;
//		memcpy(value, f.value.c_str(), f.value.size()) ;
//		memcpy(field + FIELDNAMESIZE, value, VALUESIZE) ;
//		return field ;
//	}) ;
	
//	std::vector<std::string> test ;
//
//	std::string json = struct_to_json<Field,bfzq::List>(list, [](std::vector<std::string>& item, Field f){
//		item.push_back(f.fieldName) ;
//		item.push_back(f.value) ;
//		item.push_back(f.secret? "1" : "0") ;
//	}) ;
////
//	std::cout << json << std::endl;
//
//
//	bfzq::List<Field> _json = json_to_struct<Field, bfzq::List>(json, [](bfzq::List<Field>& list, Json::Value value){
//		list.Insert(Field(value[0].asString(), value[1].asString(), value[2].asString() == "1"? true : false)) ;
//	}) ;
//
////	json
////
//	std::string __json = struct_to_json<Field,bfzq::List>(_json, [](std::vector<std::string>& item, Field f){
//		item.push_back(f.fieldName) ;
//		item.push_back(f.value) ;
//		item.push_back(f.secret? "1" : "0") ;
//	}) ;
////
//	std::cout << __json << std::endl;

//	Json::Value root;
//	Json::Value arrayObj;
//	Json::Value item;
//	
//	root["key"] = "value1";
//	for (int i=0; i<10; i++)
//	{
//		item[i] = i;
//		arrayObj.append(item);  //添加新的数组成员
//	}
//	root["array"] = arrayObj;
//	std::string out = root.toStyledString();  //将Json对象序列化为字符串
////	std::cout << root.string << std::endl ;
//	std::cout << out << std::endl;
//
//	std::string instr = "{\"asd\":123,\"dasd\":\"dd\"}" ;
//	
//	
//	Json::Reader reader ;
//	Json::Value _root ;
//	reader.parse(instr, _root) ;
//	std::cout << _root.toStyledString() << std::endl ;
//	return  0 ;
}
