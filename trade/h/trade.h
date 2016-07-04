#ifndef __TRADE_H__
#define __TRADE_H__

#include <iostream>
#include <cstring>
#include "../../h/ThostFtdcTraderApi.h"
#include "../../h/ThostFtdcUserApiStruct.h"
#include <string>
#include <vector>

using namespace std;

class TradeSpi : public CThostFtdcTraderSpi
{
	public:
		//构造函数
		TradeSpi(CThostFtdcTraderApi *tdapi);
		~TradeSpi();

		//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用
		void OnFrontConnected();

		//登录请求响应
		void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		//报单录入请求响应
		void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		//报单通知
		void OnRtnOrder(CThostFtdcOrderField *pOrder);

		//登出请求响应
		void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		//查询资金帐户响应
		void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	private:
		string USER_ID;
		string PASS;
		string BROKER;
		CThostFtdcTraderApi *tdapi;
		CThostFtdcReqUserLoginField *loginField;
		CThostFtdcReqAuthenticateField *authField;
};

#endif
