#include<stdio.h>
#include"udp_client.h"
#include"udp_data.h"

int main()
{

	udp_client client;
	client.init_client();
	
	std::string _nick_name;
	std::string _school;
	std::string _cmd = "TALK_MASSAGE";

	udp_data _client_data;

	std::cout<<"please Enter nickname:> ";
	fflush(stdout);
	std::cin>>_nick_name;

	std::cout<<"please Enter school:> ";
	fflush(stdout);
	std::cin>>_school;


	std::string msg;
	std::string send_str;
	std::string recv_str;
	while(1)
	{
		_client_data.set_nick_name(_nick_name);
		_client_data.set_school(_school);
		_client_data.set_cmd(_cmd);

		std::cout<<"please Enter:> ";
		fflush(stdout);
		std::cin>>msg;
		_client_data.set_msg(msg);
		_client_data.val_to_str(send_str);
		cout<<"send:> "<<send_str<<endl;
		client.reliable_send_msg(send_str);		

		client.reliable_recv_msg(recv_str);
		_client_data.str_to_val(recv_str);

		std::string tmp;
		_client_data.get_nick_name(tmp);
		cout<<tmp<<",";
		_client_data.get_school(tmp);
		cout<<tmp<<",";
		_client_data.get_cmd(tmp);
		cout<<tmp<<",";
		_client_data.get_msg(tmp);
		cout<<tmp<<endl;
	}
	return 0;
}
