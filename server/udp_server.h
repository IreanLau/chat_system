#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> //bzero
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include"data_pool.h" 
#define G_BLOCK_SIZE 1024

using namespace std;

class udp_server{
	public:
		udp_server(unsigned short _port = 8080);
		int init_server();
		int broadcast_msg();
		int reliable_recv_msg();
		int reliable_send_msg(std::string& _in_msg,struct sockaddr_in& client,socklen_t len);
		~udp_server();
	private:
		int sock;
		unsigned short int port;
		data_pool pool;
		std::map<std::string,struct sockaddr_in> online_user;		
		int recv_msg(std::string& _out_msg);
		int send_msg(std::string& _in_msg,struct sockaddr_in& client,socklen_t len);
		bool register_user(struct sockaddr_in& client);
};
