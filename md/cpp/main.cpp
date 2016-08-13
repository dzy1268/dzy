#include "md.h"
#include "conf.h"
#include "ip.h"
#include <pthread.h>

#define NUM 4



static void* hq(void* arg)
{
	string now;
	string settime1 = "15:50:00";
	string settime2 = "16:00:00";
	string settime3 = "03:00:00";
	string settime4 = "08:40:00";
	time_t datetime;
	ObjectMongo mongo;
	mongo.Conn();
	string db = "test";
/*	for(int j = 0; j < 10000; ++j)
	{
		sleep(60);
		if(vid == 1)
		{
			vid = 2;
			sleep(5);
			for(int i = 0; i < vp1.size(); ++i)
			{
				mongo.Insert(db + "." + vp1[i].first, vp1[i].second);
				vp1[i].second.clear();
				vp1[i].second.reserve(28800);
			}
		}
		if(vid == 2)
		{
			vid = 1;
			sleep(5);
			for(int i = 0; i < vp2.size(); ++i)
			{
				mongo.Insert(db + "." + vp2[i].first, vp2[i].second);
				vp2[i].second.clear();
				vp2[i].second.reserve(28800);
			}
		}
	}
	*/
	for(int j = 0; j < 10000; ++j)
	{
		time(&datetime);
		now = ctime(&datetime);
		for(int i = 0; i < vp1.size(); ++i)
		{
			if(vp1[i].second.size() != 0 && ((now.substr(11, 8) > settime1 && now.substr(11, 8) < settime2 ) || (now.substr(11, 8) > settime3 && now.substr(11, 8) < settime4)))
			{
				mongo.Insert(db + "." + vp1[i].first, vp1[i].second);
				vp1[i].second.clear();
				vp1[i].second.reserve(28800);
			}
		}
		for(int i = 0; i < vp2.size(); ++i)
		{
			if(vp2[i].second.size() != 0 && ((now.substr(11, 8) > settime1 && now.substr(11, 8) < settime2 ) || (now.substr(11, 8) > settime3 && now.substr(11, 8) < settime4)))
			{
				mongo.Insert(db + "." + vp2[i].first, vp2[i].second);
				vp2[i].second.clear();
				vp2[i].second.reserve(28800);
			}
		}
		sleep(1);
		j = 0;
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
	vector<Tick>* vhq1 = new vector<Tick>[argc];
	vector<Tick>* vhq2 = new vector<Tick>[argc];
	for (int i = 0; i< (argc -1); ++i)
	{
		vp1.push_back(make_pair(argv[i + 1], vhq1[i]));
		vhq1[i].reserve(28800);
		vp2.push_back(make_pair(argv[i + 1], vhq2[i]));
		vhq2[i].reserve(28800);
	}
	vid = 1;
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
