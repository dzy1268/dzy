#include "trade.h"
#include "conf.h"

//构造函数
TradeSpi::TradeSpi(CThostFtdcTraderApi *tdapi)
{
	this->tdapi = tdapi;
}

//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用
void TradeSpi::OnFrontConnected()
{
	cout << "请求登陆" << endl;
	loginField = new CThostFtdcReqUserLoginField();
	string file = "conf/server.conf";
	string key = "broker";
	Conf(key, file);
	BROKER = key;
	strcpy(loginField->BrokerID, key.c_str());
	key = "investor";
	Conf(key, file);
	USER_ID = key;
	strcpy(loginField->UserID, key.c_str());
	key = "password";
	Conf(key, file);
	PASS = key;
	strcpy(loginField->Password, key.c_str());
	tdapi->ReqUserLogin(loginField, 0);
}

//登录请求响应
void TradeSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "登录请求回调OnRspUserLogin" << endl;
	cout << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
	cout << "前置编号:" << pRspUserLogin->FrontID << endl;
	cout << "会话编号" << pRspUserLogin->SessionID << endl;
	cout << "最大报单引用:" << pRspUserLogin->MaxOrderRef << endl;
	cout << "上期所时间：" << pRspUserLogin->SHFETime << endl;
	cout << "交易日：" << tdapi->GetTradingDay() << endl;
//	tradingDate = tdapi->GetTradingDay();//设置交易日期

	CThostFtdcQryTradingAccountField *account = new CThostFtdcQryTradingAccountField();
	strcpy(account->BrokerID, BROKER.c_str());
	strcpy(account->InvestorID, USER_ID.c_str());
	tdapi->ReqQryTradingAccount(account, 999);
}

//登出请求响应
void TradeSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

//查询资金帐户响应
void TradeSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo == nullptr || pRspInfo->ErrorID == 0)
	{
		cout << "nRequestID: " << nRequestID << endl;
		cout << "可用资金" << pTradingAccount->Available << endl;
	}
}
