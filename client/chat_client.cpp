#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<vector>
#include<string>
#include<signal.h>
#include"udp_client.h"
#include"udp_data.h"
#include"window.h"

chat_window _win;
vector<std::string> list;
udp_client*  sig_client=NULL;

void* client_header(void *arg)
{
	std::string line="Welcome To WeChat of Linux!";
	int step=6;
	while(1)
	{
		_win.draw_head();
		_win.push_str_to_win(_win.get_header(),2,step++,line);
		_win.clear_win_line(_win.get_header(),3,1);
		step %= (COLS-6);
		if(step == 0) step = 6;
		usleep(100000);
		_win.clear_win_line(_win.get_header(),3,1);
		chat_window::win_refresh(_win.get_header());
	}
}


void* client_output(void *arg)
{
	udp_client* client = (udp_client*) arg;
	udp_data _data;
	std::string _msg;

	std::string nick_name;
	std::string school;
	std::string msg;
	std::string cmd;
	
	int total=1;

	_win.draw_output();
	chat_window::win_refresh(_win.get_output());
	while(1)
	{
		client->reliable_recv_msg(_msg);
		_data.str_to_val(_msg);
	//	cout<<"AAAAAAA"<<_msg<<endl;

		_data.get_nick_name(nick_name);
		_data.get_school(school);
		_data.get_msg(msg);
		_data.get_cmd(cmd);
		
		bool flag = true;
		if(cmd == "MESSAGE")
		{
			std::string show_msg=nick_name;
			show_msg+="-";

			show_msg+=school;
			vector<string>::iterator _iter=list.begin();
			for(;_iter!=list.end();++_iter)
			{
				if(*_iter==show_msg)
					flag=false;
			}
			if(flag)
				list.push_back(show_msg);
			show_msg+=": ";

			show_msg+=msg;
			//cout<<"AAAAAAAAAAAAAAAAAAAAAAA"<<show_msg<<endl;
			_win.push_str_to_win(_win.get_output(),total++,2,show_msg);
			chat_window::win_refresh(_win.get_output());

			total %=(LINES*3/5 -1);
			if(total==0) 
			{
				total=1;
				chat_window::win_refresh(_win.get_output());
				_win.clear_win_line(_win.get_output(),1,(LINES*3/5 -1));
			}
		}
		usleep(100000);
	}
}
void* client_input(void *arg)
{
	udp_client* client = (udp_client*) arg;
	std::string msg="Please Enter:";
	std::string _client_msg;
	std::string name;
	std::string school;
	std::string cmd="MESSAGE";

	_win.draw_input();
	chat_window::win_refresh(_win.get_input());
	_win.push_str_to_win(_win.get_input(),1,2,"Please Enter Name:");
	_win.get_str_to_win(_win.get_input(),name);

	_win.draw_input();
	chat_window::win_refresh(_win.get_input());
	_win.push_str_to_win(_win.get_input(),1,2,"Please Enter School:");
	_win.get_str_to_win(_win.get_input(),school);

	std::string send_str;
	udp_data _data;
	while(1)
	{
		_win.draw_input();
		chat_window::win_refresh(_win.get_input());

		_win.push_str_to_win(_win.get_input(),1,2,msg);
		_win.get_str_to_win(_win.get_input(),_client_msg);

		_data.set_nick_name(name);
		_data.set_school(school);
		_data.set_cmd(cmd);
		_data.set_msg(_client_msg);
		
		_data.val_to_str(send_str);
		client->reliable_send_msg(send_str);

		usleep(10000);
		_win.clear_win_line(_win.get_input(),1,1);
	}
}
void* client_list(void *arg)
{
	_win.draw_list();
	while(1)
	{
		int i=0;
		int len=list.size();

		for(;i<len;++i)
		{
			_win.push_str_to_win(_win.get_list(),i+1,2,list[i]);
		}
		chat_window::win_refresh(_win.get_list());
		usleep(10000);
	}
}

void handler(int sig)
{

	udp_data _data;
	string name="lau";
	string school="xgd";
	string cmd="CMD_QUIT";
	string _client_msg="NONE";
	
	switch(sig)
	{
	case SIGINT: 
		{
			string send_str;

			_data.set_nick_name(name);
			_data.set_school(school);
			_data.set_cmd(cmd);
			_data.set_msg(_client_msg);
			_data.val_to_str(send_str);
			sig_client->reliable_send_msg(send_str);
			exit(1);
		}
		break;
	default:
		break;
	}
}

int main()
{	
	udp_client client;
	client.init_client();
	sig_client=&client;
	_win.init();

	signal(SIGINT,handler);

	pthread_t header,output,input,list;
	
	sleep(1);
	pthread_create(&header,NULL,client_header,NULL);
	pthread_create(&output,NULL,client_output,(void*)&client);
	pthread_create(&input,NULL,client_input,(void*)&client);
	pthread_create(&list,NULL,client_list,NULL);

//	while(1)
//	{
//		usleep(10000);
//		chat_window::win_refresh(_win.get_header());
//		chat_window::win_refresh(_win.get_output());
//		chat_window::win_refresh(_win.get_list());
//		chat_window::win_refresh(_win.get_input());
//	}
	
	pthread_join(header,NULL);
	pthread_join(output,NULL);
	pthread_join(input,NULL);
	pthread_join(list,NULL);
	
	std::string _nick_name;
	std::string _school;
	std::string _cmd = "MASSAGE";

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
