#include "md.h"
#include "conf.h"

vector<char*> vec;
vector<string> vhq1;
vector<string> vhq2;
vector<string> *vhq;
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
	char buffer[500];

	string jyr = pDepthMarketData->TradingDay;
	string hydm = pDepthMarketData->InstrumentID;
	string jysdm = pDepthMarketData->ExchangeID;
	string hyszjysddm = pDepthMarketData->ExchangeInstID;
	gcvt(pDepthMarketData->LastPrice, 500, buffer);
	string zxj = buffer;
	gcvt(pDepthMarketData->PreSettlementPrice, 500, buffer);
	string scjsj = buffer;
	gcvt(pDepthMarketData->PreClosePrice, 500, buffer);
	string zsp = buffer;
	gcvt(pDepthMarketData->PreOpenInterest, 500, buffer);
	string zccl = buffer;
	gcvt(pDepthMarketData->PreOpenInterest, 500, buffer);
	string jkp = buffer;
	gcvt(pDepthMarketData->HighestPrice, 500, buffer);
	string zgj = buffer;
	gcvt(pDepthMarketData->LowestPrice, 500, buffer);
	string zdj = buffer;
	gcvt(pDepthMarketData->Volume, 500, buffer);
	string sl = buffer;
	gcvt(pDepthMarketData->Turnover, 500, buffer);
	string cjje = buffer;
	gcvt(pDepthMarketData->OpenInterest, 500, buffer);
	string ccl = buffer;
	gcvt(pDepthMarketData->ClosePrice, 500, buffer);
	string jsp = buffer;
	gcvt(pDepthMarketData->SettlementPrice, 500, buffer);
	string bcjsj = buffer;
	gcvt(pDepthMarketData->UpperLimitPrice, 500, buffer);
	string ztbj = buffer;
	gcvt(pDepthMarketData->LowerLimitPrice, 500, buffer);
	string dtbj = buffer;
	gcvt(pDepthMarketData->PreDelta, 500, buffer);
	string zxsd = buffer;
	gcvt(pDepthMarketData->CurrDelta, 500, buffer);
	string jxsd = buffer;
	string zhxgsj = pDepthMarketData->UpdateTime;
	gcvt(pDepthMarketData->UpdateMillisec, 500, buffer);
	string zhxghm = buffer;
	gcvt(pDepthMarketData->BidPrice1, 500, buffer);
	string smj1 = buffer;
	gcvt(pDepthMarketData->BidVolume1, 500, buffer);
	string sml1 = buffer;
	gcvt(pDepthMarketData->AskPrice1, 500, buffer);
	string ssj1 = buffer;
	gcvt(pDepthMarketData->AskVolume1, 500, buffer);
	string ssl1 = buffer;

        gcvt(pDepthMarketData->BidPrice2, 500, buffer);
        string smj2 = buffer;
        gcvt(pDepthMarketData->BidVolume2, 500, buffer);
        string sml2 = buffer;
        gcvt(pDepthMarketData->AskPrice2, 500, buffer);
        string ssj2 = buffer;
        gcvt(pDepthMarketData->AskVolume2, 500, buffer);
        string ssl2 = buffer;

        gcvt(pDepthMarketData->BidPrice3, 500, buffer);
        string smj3 = buffer;
        gcvt(pDepthMarketData->BidVolume3, 500, buffer);
        string sml3 = buffer;
        gcvt(pDepthMarketData->AskPrice3, 500, buffer);
        string ssj3 = buffer;
        gcvt(pDepthMarketData->AskVolume3, 500, buffer);
        string ssl3 = buffer;

        gcvt(pDepthMarketData->BidPrice4, 500, buffer);
        string smj4 = buffer;
        gcvt(pDepthMarketData->BidVolume4, 500, buffer);
        string sml4 = buffer;
        gcvt(pDepthMarketData->AskPrice4, 500, buffer);
        string ssj4 = buffer;
        gcvt(pDepthMarketData->AskVolume4, 500, buffer);
        string ssl4 = buffer;

        gcvt(pDepthMarketData->BidPrice5, 500, buffer);
        string smj5 = buffer;
        gcvt(pDepthMarketData->BidVolume5, 500, buffer);
        string sml5 = buffer;
        gcvt(pDepthMarketData->AskPrice5, 500, buffer);
        string ssj5 = buffer;
        gcvt(pDepthMarketData->AskVolume5, 500, buffer);
        string ssl5 = buffer;
	
		

	string sql = jyr + "," + hydm + "," + jysdm + "," + hyszjysddm + "," + zxj + "," + scjsj + "," + zsp + "," + zccl + "," + jkp + "," + zgj + "," + zdj + "," + sl + "," + cjje + "," + ccl + "," + jsp + "," + bcjsj + "," + ztbj + "," + dtbj + "," + zxsd + "," + jxsd + ",'" + zhxgsj + "'," + zhxghm + "," + smj1 + "," + sml1 + "," + ssj1 + "," + ssl1 + "," + smj2 + "," + sml2 + "," + ssj2 + "," + ssl2 + "," + smj3 + "," + sml3 + "," + ssj3 + "," + ssl3 + "," + smj4 + "," + sml4 + "," + ssj4 + "," + ssl4 + "," + smj5 + "," + sml5 + "," + ssj5 + "," + ssl5;
	pthread_mutex_lock(&mutex);
	vhq->push_back(sql);
	pthread_mutex_unlock(&mutex);
}
