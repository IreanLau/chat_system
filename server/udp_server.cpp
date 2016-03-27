#include"udp_server.h"
#include"udp_data.h"



static void print_log(std::string _log)
{
	std::cerr<<_log<<std::endl;
}

bool udp_server::register_user(struct sockaddr_in& client)
{

	std::string _ip_key= inet_ntoa(client.sin_addr);
	print_log(_ip_key);
	std::map<std::string,struct sockaddr_in>::iterator _iter=online_user.find(_ip_key);
	if(_iter != online_user.end())
	{
		return false;
	}

	online_user.insert(make_pair(_ip_key,client));
	print_log("regis done..");
	return true;
}

udp_server::udp_server(unsigned short int _port)
	:port(_port)
{

}

udp_server::~udp_server()
{
	if(sock>0)
		close(sock);
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

int udp_server::reliable_recv_msg()//输出型参数
{
	std::string _out_msg;
	int ret = recv_msg(_out_msg);
	if(ret > 0)
	{
//		print_log("reliable_recv");
		print_log(_out_msg);
		pool.put_msg(_out_msg);
//		print_log("after put");

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
	 //recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);
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
		//keep->online_user
		register_user(client);
	}
	return _size;
}

int udp_server::reliable_send_msg(std::string& _in_msg,struct sockaddr_in& client,socklen_t len)//输出型参数
{
	return send_msg( _in_msg,client, len);//输出型参数
}
int udp_server::send_msg(std::string& _in_msg,struct sockaddr_in& client,socklen_t len)//输出型参数
{
	//sendto
	ssize_t _size = sendto(sock,_in_msg.c_str(),_in_msg.size(),0,(sockaddr*)&client,len);
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
	std::string msg;
	pool.get_msg(msg);


	std::map<std::string,struct sockaddr_in>::iterator _iter = online_user.begin();
	for(;_iter != online_user.end();++_iter)
	{
		print_log("broadcast");
		print_log(msg);
		
		udp_data _data;
		string _cmd;
		_data.str_to_val(msg);
		_data.get_cmd(_cmd);
		if(_cmd=="CMD_QUIT")
		{
			string _ip_key= inet_ntoa(_iter->second.sin_addr);
			print_log("client close...");
			cout<<_ip_key<<"  :>will deadline..."<<endl;
			online_user.erase(_ip_key);
			return 0;
		}

		reliable_send_msg(msg,_iter->second,sizeof(_iter->second));
	}
	return 0;
}
