#pragma once
#include<iostream>
#include<string>
#include"my_json.h"
using namespace std;

class udp_data{
	public:
		udp_data();
		~udp_data();

		bool val_to_str(std::string& _out_msg);
		bool str_to_val(std::string& _in_msg);

		void set_nick_name(const std::string& _s)
		{
			nick_name=_s;
		}
		void set_school(const std::string& _s)
		{
			school=_s;
		}
		void set_msg(const std::string& _s)
		{
			msg=_s;
		}
		void set_cmd(const std::string& _s)
		{
			cmd=_s;
		}

		void get_nick_name(std::string& _s)
		{
			_s=nick_name;
		}
		void get_school(std::string& _s)
		{
			_s=school;
		}
		void get_msg(std::string& _s)
		{
			_s=msg;
		}
		void get_cmd(std::string& _s)
		{
			_s=cmd;
		}
	private:
		std::string nick_name;
		std::string school;
		std::string msg;
		std::string cmd;//是否下线
};
