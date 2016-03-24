#pragma once

#include<iostream>
#include<string>
#include<json/json.h>


using namespace std;

#define G_BLOCK_SZIE 1024

class my_json{
	public:
		my_json();
		~my_json();
		static int _serialize(Json::Value &_in_val,std::string& str_out);
		static int _deserialize(string &_in_val,Json::Value& _val_out);
};
