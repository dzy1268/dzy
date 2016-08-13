#include "md.h"
#include "conf.h"

int vid;
vector<char*> vec;
vector<pair<string, vector<Tick> > > vp1;
vector<pair<string, vector<Tick> > > vp2;

pthread_mutex_t mutex;

MdSpi::MdSpi(CThostFtdcMdApi *mdApi)
{
	this->mdApi = mdApi;
}

MdSpi::~MdSpi(){}

void MdSpi::OnFrontConnected()
{
	loginRequestID = 0;
	CThostFtdcReqUserLoginField reqUserLogin;
	string file = "conf/server.conf";
	string key = "broker";
	Conf(key, file);
	strcpy(reqUserLogin.BrokerID, key.c_str());
	key = "investor";
	Conf(key, file);
	strcpy(reqUserLogin.UserID, key.c_str());
	key = "password";
	Conf(key, file);
	strcpy(reqUserLogin.Password, key.c_str());
	mdApi->ReqUserLogin(&reqUserLogin, loginRequestID);
}

void MdSpi::OnFrontDisconnected(int nReason)
{
	cout << "OnFrontDisconnected" << endl;
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if(pRspInfo->ErrorID != 0)
	{
		cout << "ErrorCode: " << pRspInfo->ErrorID << " ErrorMsg: " << pRspInfo->ErrorMsg << endl;
		exit(-1);
	}
	cout << "登陆成功\n";
	if (ins > 0)
	{
		char* Instrumnet[ins];
		for (int i = 0; i < ins; ++i)
		{
			Instrumnet[i] = vec[i];
		}
	mdApi->SubscribeMarketData (Instrumnet, ins);
	}
}

void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
	
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "合约代码:" << pSpecificInstrument->InstrumentID << endl;
	cout << "应答信息:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	struct timeval begin;
	struct timeval end;
	gettimeofday(&begin, NULL);
	Tick tick;
	tick.jyr = pDepthMarketData->TradingDay;
	tick.hydm = pDepthMarketData->InstrumentID;
	tick.jysdm = pDepthMarketData->ExchangeID;
	tick.hyszjysddm = pDepthMarketData->ExchangeInstID;
	if (pDepthMarketData->LastPrice > 3.4e+38)
	{
		tick.zxj = 0;
	}
	else
	{
		tick.zxj = pDepthMarketData->LastPrice;
	}
	if (pDepthMarketData->PreSettlementPrice > 3.4e+38)
	{
		tick.scjsj = 0;
	}
	else
	{
		tick.scjsj = pDepthMarketData->PreSettlementPrice;
	}
	if (pDepthMarketData->PreClosePrice > 3.4e+38)
	{
		tick.zsp = 0;
	}
	else
	{
		tick.zsp = pDepthMarketData->PreClosePrice;
	}
	tick.zccl = pDepthMarketData->PreOpenInterest;
	if (pDepthMarketData->PreOpenInterest > 3.4e+38)
	{
		tick.jkp = 0;
	}
	else
	{
		tick.jkp = pDepthMarketData->PreOpenInterest;
	}
	if (pDepthMarketData->HighestPrice > 3.4e+38)
	{
		tick.zgj = 0;
	}
	else
	{
		tick.zgj = pDepthMarketData->HighestPrice;
	}
	if (pDepthMarketData->LowestPrice > 3.4e+38)
	{
		tick.zdj = 0;
	}
	else
	{
		tick.zdj = pDepthMarketData->LowestPrice;
	}
	tick.sl = pDepthMarketData->Volume;
	if (pDepthMarketData->Turnover > 3.4e+38)
	{
		tick.cjje = 0;
	}
	else
	{
		tick.cjje = pDepthMarketData->Turnover;
	}
	tick.ccl = pDepthMarketData->OpenInterest;
	if (pDepthMarketData->ClosePrice > 3.4e+38)
	{
		tick.jsp = 0;
	}
	else
	{
		tick.jsp = pDepthMarketData->ClosePrice;
	}
	if (pDepthMarketData->SettlementPrice > 3.4e+38)
	{
		tick.bcjsj = 0;
	}
	else
	{
		tick.bcjsj = pDepthMarketData->SettlementPrice;
	}
	if (pDepthMarketData->UpperLimitPrice > 3.4e+38)
	{
		tick.ztbj = 0;
	}
	else
	{
		tick.ztbj = pDepthMarketData->UpperLimitPrice;
	}
	if (pDepthMarketData->LowerLimitPrice > 3.4e+38)
	{
		tick.dtbj = 0;
	}
	else
	{
		tick.dtbj = pDepthMarketData->LowerLimitPrice;
	}
	if (pDepthMarketData->PreDelta > 3.4e+38)
	{
		tick.zxsd = 0;
	}
	else
	{
		tick.zxsd = pDepthMarketData->PreDelta;
	}
	if (pDepthMarketData->CurrDelta > 3.4e+38)
	{
		tick.jxsd = 0;
	}
	else
	{
		tick.jxsd = pDepthMarketData->CurrDelta;
	}
	tick.zhxgsj = pDepthMarketData->UpdateTime;
	tick.zhxghm = pDepthMarketData->UpdateMillisec;
	if (pDepthMarketData->BidPrice1 > 3.4e+38)
	{
		tick.smj1 = 0;
	}
	else
	{
		tick.smj1 = pDepthMarketData->BidPrice1;
	}
	tick.sml1 = pDepthMarketData->BidVolume1;
	if (pDepthMarketData->AskPrice1 > 3.4e+38)
	{
		tick.ssj1 = 0;
	}
	else
	{
		tick.ssj1 = pDepthMarketData->AskPrice1;
	}
	tick.ssl1 = pDepthMarketData->AskVolume1;
	if (pDepthMarketData->BidPrice2 > 3.4e+38)
	{
		tick.smj2 = 0;
	}
	else
	{
		tick.smj2 = pDepthMarketData->BidPrice2;
	}
        tick.sml2 = pDepthMarketData->BidVolume2;
        if (pDepthMarketData->AskPrice2 > 3.4e+38)
	{
		tick.ssj2 = 0;
	}
	else
	{
		tick.ssj2 = pDepthMarketData->AskPrice2;
	}
        tick.ssl2 = pDepthMarketData->AskVolume2;
	if (pDepthMarketData->BidPrice3 > 3.4e+38)
	{
		tick.smj3 = 0;
	}
	else
	{
		tick.smj3 = pDepthMarketData->BidPrice3;
	}
        tick.sml3 = pDepthMarketData->BidVolume3;
        if (pDepthMarketData->AskPrice3 > 3.4e+38)
	{
		tick.ssj3 = 0;
	}
	else
	{
		tick.ssj3 = pDepthMarketData->AskPrice3;
	}
        tick.ssl3 = pDepthMarketData->AskVolume3;
	if (pDepthMarketData->BidPrice4 > 3.4e+38)
	{
		tick.smj4 = 0;
	}
	else
	{
		tick.smj4 = pDepthMarketData->BidPrice4;
	}
        tick.sml4 = pDepthMarketData->BidVolume4;
        if (pDepthMarketData->AskPrice4 > 3.4e+38)
	{
		tick.ssj4 = 0;
	}
	else
	{
		tick.ssj4 = pDepthMarketData->AskPrice4;
	}
        tick.ssl4 = pDepthMarketData->AskVolume4;
	if (pDepthMarketData->BidPrice5 > 3.4e+38)
	{
		tick.smj5 = 0;
	}
	else
	{
		tick.smj5 = pDepthMarketData->BidPrice5;
	}
        tick.sml5 = pDepthMarketData->BidVolume5;
        if (pDepthMarketData->AskPrice5 > 3.4e+38)
	{
		tick.ssj5 = 0;
	}
	else
	{
		tick.ssj5 = pDepthMarketData->AskPrice5;
	}
        tick.ssl5 = pDepthMarketData->AskVolume5;

	if (vid == 1)
	{
		for (int i = 0; i < vp1.size(); ++i)
		{
			if(tick.hydm == vp1[i].first)
			{
				pthread_mutex_lock(&mutex);
				vp1[i].second.push_back(tick);
				pthread_mutex_unlock(&mutex);
			}
		}
	}
	else
	{
		for (int i = 0; i < vp2.size(); ++i)
		{
			if(tick.hydm == vp2[i].first)
			{
				pthread_mutex_lock(&mutex);
				vp2[i].second.push_back(tick);
				pthread_mutex_unlock(&mutex);
			}
		}
	}
	
	gettimeofday(&end, NULL);
	if ((long)(end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec > 50000)
	{
		cout << tick.zhxgsj << " " << tick.hydm << endl;
	}
}
