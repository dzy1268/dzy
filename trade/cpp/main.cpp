#include "trade.h"
#include "conf.h"
#include "ip.h"

int main(int argc, char* argv[])
{
	string file = "conf/server.conf";
	string key = "server";
	string s;
	Conf(key, file);
	int j = 0;
	for (int i = 0; i < key.size(); ++i)
	{
		if(key[i] == ';')
		{
			s = key.substr(j, i - j);
			j = i + 1;
			if ( T_c(s) == '0' )
			{
				break;
			}
		}
	}
	char *server;
	const int len = s.length();
	server = new char[len + 1];
	strcpy(server, s.c_str());

	CThostFtdcTraderApi *tdapi = CThostFtdcTraderApi::CreateFtdcTraderApi("./flow/");
	//auto tdapi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	TradeSpi *tdspi = new TradeSpi(tdapi);
	//注册事件处理对象
	tdapi->RegisterSpi(tdspi);
	//订阅共有流和私有流
	tdapi->SubscribePublicTopic(THOST_TERT_RESTART);
	tdapi->SubscribePrivateTopic(THOST_TERT_RESTART);
	//注册前置机
	tdapi->RegisterFront(server);
	tdapi->Init();
	tdapi->Join();
	return 0;
}
