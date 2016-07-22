#include "trade.h"
#include "conf.h"
#include "ip.h"
#include "redis.h"
#include <pthread.h>

static void* th(void* arg)
{
	CThostFtdcTraderApi *tdapi = CThostFtdcTraderApi::CreateFtdcTraderApi("./flow/");
	TradeSpi *tdspi = new TradeSpi(tdapi);
	tdapi->RegisterSpi(tdspi);
	tdapi->RegisterFront("tcp://180.168.146.187:10001");
	tdapi->SubscribePublicTopic(THOST_TERT_RESTART);
	tdapi->SubscribePrivateTopic(THOST_TERT_RESTART);
	tdapi->Init();
	tdapi->Join();
	tdapi->Release();
}

int main(int argc, char* argv[])
{
	pthread_t tid;
	int ret = pthread_create(&tid, NULL, &th, NULL);
	//pthread_join(tid, NULL);
	sleep (10);
	//pthread_exit(NULL);
	return 0;
}
