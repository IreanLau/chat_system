#include"data_pool.h"


data_pool::data_pool(int _size)
	:pool_size(_size)
	 ,pool(POOL_SIZE)
{	
	start=end=0;
	sem_init(&product_sem,0,POOL_SIZE);
	sem_init(&consumer_sem,0,0);
}
data_pool::~data_pool()
{
	sem_destroy(&product_sem);
	sem_destroy(&consumer_sem);
}

bool data_pool::get_msg(std::string& msg)
{
	sem_wait(&consumer_sem);
	msg=pool[end];
	end=(++end)%pool_size;
	sem_post(&product_sem);
	return true;
}
bool data_pool::put_msg(std::string& msg)
{
	sem_wait(&product_sem);//p
	pool[start]=msg;
	start=(++start)%pool_size;
	sem_post(&consumer_sem);
	return true;
}
