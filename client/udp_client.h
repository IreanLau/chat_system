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

#define G_BLOCK_SIZE 1024

using namespace std;


class udp_client{
	public:
		udp_client(std::string _remote_ip ="127.0.0.1",unsigned short _port = 8080);
		int init_client();
		int reliable_recv_msg(string& _out_msg);
		int reliable_send_msg(string& _in_msg);
		~udp_client();
	private:
		int sock;
		std::string remote_ip;
		unsigned short remote_port;
};
