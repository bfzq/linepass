//
//  netstruct.hpp
//  index
//
//  Created by 猪摇摇 on 2018/11/13.
//  Copyright © 2018 bfzq. All rights reserved.
//

#ifndef netstruct_hpp
#define netstruct_hpp

#include <stdio.h>
#include <string>
#include <functional>
#include <vector>
#include <json.h>
#include "list.hpp"
#include "struct.h"


template <typename T,
template <typename P> class L>
Json::Value struct_to_json_struct(L<T> s, std::function<void(std::vector<std::string>& item, T t)> f) {
	Json::Value json ;
	s.foreach([&json, &f](T t) {
		std::vector<std::string> item ;
		f(item, t) ;
		Json::Value jsonItem ;
		for (int i = 0; i < item.size(); i++) {
			jsonItem[i] = item[i] ;
		}
		json.append(jsonItem) ;
	}) ;
	return json ;
}

template <typename T,
template <typename P> class L>
std::string struct_to_json(L<T> s, std::function<void(std::vector<std::string>& item, T t)> f) {
	return struct_to_json_struct<T,L>(s, f).toStyledString() ;
}




template <typename T,
template <typename P> class L>
L<T> json_to_struct(std::string json, std::function<void(L<T>& list, Json::Value value)> f) {
	Json::Reader reader ;
	Json::Value root ;
	L<T> _struct ;
	if (reader.parse(json, root)) {
		for (Json::Value& value : root) {
			f(_struct, value) ;
		}
	}
	return _struct ;
}

template <typename T,
template <typename P> class L>
L<T> json_to_struct(std::string json, std::function<T(Json::Value::Members::iterator iter, Json::Value value)> f) {
	Json::Reader reader ;
	Json::Value root ;
	L<T> _struct ;
	if (reader.parse(json, root)) {
		Json::Value::Members members = root.getMemberNames() ;// 获取所有key
		for (Json::Value::Members::iterator iter = members.begin(); iter != members.end() ;iter++) {
			_struct.Insert(f(iter,root[(*iter).c_str()])) ;
		}
	}
	return _struct ;
}


template <typename T,
template <typename P> class L>
L<T> json_to_struct(std::string json, std::function<T(Json::Value::Members::iterator iter, std::string json)> f) {
	Json::Reader reader ;
	Json::Value root ;
	L<T> _struct ;
	if (reader.parse(json, root)) {
		Json::Value::Members members = root.getMemberNames() ;// 获取所有key
		for (Json::Value::Members::iterator iter = members.begin(); iter != members.end() ;iter++) {
			_struct.Insert(f(iter,root[(*iter).c_str()].toStyledString())) ;
		}
	}
	return _struct ;
}

#endif /* netstruct_hpp */
