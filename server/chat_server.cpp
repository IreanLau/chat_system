#include"udp_server.h"

static void usage(string proc)
{
	cout<<"use:> "<<proc<<" [port]"<<endl;
}

void* consumer_run(void *arg)
{
	udp_server *s = (udp_server*)arg;
	while(1)
	{
		std::cout<<"consumer run..."<<std::endl;
		s->broadcast_msg();
	}
	return NULL;
}

void* producter_run(void *arg)
{
	udp_server *s = (udp_server*)arg;
	while(1)
	{
		std::cout<<"producter run..."<<std::endl;
		s->reliable_recv_msg();
	}
	return NULL; 
}

int main(int argc,char*argv[])
{

	if(argc!=2)
	{
		usage(argv[0]);
		exit(1);
	}

	//daemon(0,0);

	int port=atoi(argv[1]);
	udp_server serd(port);
	serd.init_server();
	pthread_t consumer,producter;
	pthread_create(&consumer,NULL,consumer_run,(void*)&serd);
	pthread_create(&producter,NULL,producter_run,(void*)&serd);
	pthread_join(consumer,NULL);
	pthread_join(producter,NULL);

//	while(1)
//	{
//		string inmsg;
//		service.reliable_recv_msg(inmsg);
//		cout<<inmsg.c_str()<<endl;
//	}

	return 0;
}
