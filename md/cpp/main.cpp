#include "md.h"
#include "conf.h"
#include "ip.h"
#include <pthread.h>

#define NUM 4



static void* hq(void* arg)
{
	string sql;
	int z = 0;
	string now;
	string settime1 = "15:50:00";
	string settime2 = "16:00:00";
	string settime3 = "03:00:00";
	string settime4 = "08:40:00";
	time_t timel;
	ObjectRedis redis;
	ObjectMysql mysql;
	for(int i = 0; i < 65535; ++i)
	{
		if(vhq1.size() > 18000000)
		{
			pthread_mutex_lock(&mutex);
			vhq = &vhq2;
			pthread_mutex_unlock(&mutex);
			redis.Connect();
			for (int j = 0; j < vhq1.size(); ++j)
			{
				redis.Insert(vhq1[j]);
			}
			redis.disConnect();
			mysql.Connect();
			for (int j = 0; j < vhq1.size(); ++j)
			{
				mysql.Insert(vhq1[j]);
			}
			mysql.disConnect();
			vhq1.clear();
			vector<Tick>().swap(vhq1);
			vhq1.reserve(20000000);
		}
		if(vhq2.size() > 18000000)
		{
			pthread_mutex_lock(&mutex);
			vhq = &vhq1;
			pthread_mutex_unlock(&mutex);
			redis.Connect();
			for (int j = 0; j < vhq2.size(); ++j)
			{
				redis.Insert(vhq2[j]);
			}
			redis.disConnect();
			mysql.Connect();
			for (int j = 0; j < vhq2.size(); ++j)
			{
				mysql.Insert(vhq2[j]);
			}
			mysql.disConnect();
			vhq2.clear();
			vector<Tick>().swap(vhq2);
			vhq2.reserve(20000000);
		}
		z = vhq->size();
		time(&timel);
		now = ctime(&timel);
		sleep(1);
		if (z == vhq->size() && z != 0 &&((now.substr(11, 8) > settime1 && now.substr(11, 8) < settime2 ) || (now.substr(11, 8) > settime3 && now.substr(11, 8) < settime4)))
		{
			pthread_mutex_lock(&mutex);
			vhq = &vhq1;
			pthread_mutex_unlock(&mutex);
			redis.Connect();
			for (int j = 0; j < vhq2.size(); ++j)
			{
				redis.Insert(vhq2[j]);
				mysql.Insert(vhq2[j]);
			}
			redis.disConnect();
//			mysql.Connect();
//			for (int j = 0; j < vhq2.size(); ++j)
//			{
//				mysql.Insert(vhq2[j]);
//			}
//			mysql.disConnect();
			vhq2.clear();
			vector<Tick>().swap(vhq2);
			vhq2.reserve(20000000);

			pthread_mutex_lock(&mutex);
			vhq = &vhq2;
			pthread_mutex_unlock(&mutex);
			redis.Connect();
			for (int j = 0; j < vhq1.size(); ++j)
			{
				redis.Insert(vhq1[j]);
			}
			redis.disConnect();
//			mysql.Connect();
//			for (int j = 0; j < vhq1.size(); ++j)
//			{
//				mysql.Insert(vhq1[j]);
//			}
//			mysql.disConnect();
			vhq1.clear();
			vector<Tick>().swap(vhq1);
			vhq1.reserve(20000000);

			i = 0;
		}
		cout << now << " vector : " << z << endl;

	}
}

static void* th(void* arg)
{
	pthread_mutex_lock(&mutex);
	vec.clear();
	struct args *argt;
	argt = (struct args *) arg;
	CThostFtdcMdApi* pUserApi = CThostFtdcMdApi::CreateFtdcMdApi("./flow/",false,false);
	MdSpi sh(pUserApi);
	sh.ins = argt->insp;
	for(int i = 0; i < sh.ins; ++i)
	{
		vec.push_back(argt->vecp[i]);
	}
	pthread_mutex_unlock(&mutex);
	pUserApi->RegisterSpi(&sh);
	char ip[] = "tcp://180.168.214.246:41213";
	pUserApi->RegisterFront(ip);
	pUserApi->Init();
	pUserApi->Join();
	pUserApi->Release();
}

int main(int argc, char* argv[])
{
//	vector<Tick> vr;
	vhq1.reserve(20000000);
	vhq2.reserve(20000000);
	vhq = &vhq1;
	struct args arg[NUM];

	int n = (argc - 1) / NUM;
	int z = 0;

	for(int i = 0; i < (NUM - 1) ; ++i)
	{
		arg[i].insp = n;
		for(int j = z; j < (z + n); ++j)
		{
			arg[i].vecp.push_back(argv[j + 1]);
		}
		z += n;
	}
	arg[NUM - 1].insp = ((argc - 1) % NUM) + n ;
	for (int j = z; j < (argc - 1); ++j)
	{
		arg[NUM - 1].vecp.push_back(argv[j + 1]);
	}

	pthread_t tids[NUM + 1];
	pthread_mutex_init(&mutex, NULL);
	for(int i = 0; i < NUM; ++i)
	{
		int ret = pthread_create(&tids[i], NULL, &th, &arg[i]);
		sleep(1);
	}
	int ret = pthread_create(&tids[NUM], NULL, &hq, NULL);
	for(int i = 0; i < NUM + 1; ++i)
	{
		pthread_join(tids[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);

}
