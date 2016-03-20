#include"udp_server.h"



static void print_log(std::string _log)
{
	std::cerr<<_log<<std::endl;
}


udp_server::udp_server(unsigned short int _port)
	:port(_port)
{

}

udp_server::~udp_server()
{
}


//if success return 0
//else exit
int udp_server::init_server()
{
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		print_log ((strerror(errno)));
		exit(1);
	}
	
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr= htonl(INADDR_ANY);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		print_log(strerror(errno));
		exit(1);
	}
	return 0;
}

int udp_server::reliable_recv_msg(string& _out_msg)//输出型参数
{
	int ret = recv_msg(_out_msg);
	if(ret > 0)
	{
		//pool.put_msg(_out_msg);
		return ret;
	}
	return -1;
}

int udp_server::recv_msg(std::string& _out_msg)//输出型参数
{
	char buf[G_BLOCK_SIZE];
	bzero(buf,sizeof(buf));
	struct sockaddr_in client;
	socklen_t len=sizeof(client);
	// recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);
	ssize_t _size = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
	if(_size < 0)
	{
		print_log(strerror(errno));
		_out_msg="";
		return 1;
	}
	else if(_size >= 0)
	{
		_out_msg=buf;
	}
	return 0;
}

int udp_server::reliable_send_msg(std::string& _in_msg,struct sockaddr_in* client,socklen_t len)//输出型参数
{
	return send_msg( _in_msg,client, len);//输出型参数
}
int udp_server::send_msg(std::string& _in_msg,struct sockaddr_in* client,socklen_t len)//输出型参数
{
	//sendto
	ssize_t _size = sendto(sock,_in_msg.c_str(),_in_msg.size(),0,(sockaddr*)client,len);
	if(_size < 0)
	{
		print_log(strerror(errno));
		return 1;
	}
	else
	{

	}
	return 0;
}

int udp_server::broadcast_msg()
{
	//std::string msg = pool.get_msg();
	std::map<std::string,struct sockaddr_in>::iterator _iter = online_user.begin();
	for(;_iter != online_user.end();++_iter)
	{
		//reliable_send_msg(msg,_iter->second,sizeof(_iter->second));


	}
	return 0;
}
