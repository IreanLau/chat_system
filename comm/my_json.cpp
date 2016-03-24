#include"my_json.h"

my_json::my_json()
{

}
my_json::~my_json()
{

}

int my_json::_serialize(Json::Value &_in_val,std::string& str_out)
{
#ifdef _STYLE_
	Json::StyleWriter _write;
#else
	Json::FastWriter _write;
#endif

	str_out = _write.write(_in_val);
	return 0;
}

int my_json::_deserialize(std::string&_in_val,Json::Value& _val_out)
{
	Json::Reader _reader;
	if(_reader.parse(_in_val,_val_out,false) )
		return 0;
	else
		return 1;
}

//int main()
//{
//	Json::Value _val;
//	string _str_out;
//	_val["nick_name"]="fly pig";
//	_val["school"]="XATU";
//	_val["msg"]="nihao";
//	my_json::_serialize(_val, _str_out);
//	cout<<_str_out<<endl;
//	return 0;
//}

