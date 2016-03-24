#include"udp_data.h"
#include"my_json.h"

udp_data::udp_data()
{

}

udp_data::~udp_data()
{

}

bool udp_data::val_to_str(std::string& _out_msg)//序列化
{
	Json::Value _val;
	//key->val
	_val["nick_name"]=nick_name;
	_val["school"]=school;
	_val["msg"]=msg;
	_val["cmd"]=cmd;
	
	my_json::_serialize(_val,_out_msg);
}

bool udp_data::str_to_val(std::string & _in_msg)//反序列化
{
	Json::Value _val_out;
	//val->key
	my_json::_deserialize(_in_msg,_val_out);

	nick_name = _val_out["nick_name"].asString();
	school = _val_out["school"].asString();
	msg = _val_out["msg"].asString();
	cmd = _val_out["cmd"].asString();
}
