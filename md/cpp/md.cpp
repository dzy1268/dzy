#include "md.h"
#include "conf.h"

vector<char*> vec;

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
	cout << pDepthMarketData->InstrumentID << " " << pDepthMarketData->LastPrice << " " << pDepthMarketData->UpdateTime << endl;
}
