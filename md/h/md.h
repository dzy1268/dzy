#ifndef __MD_H__
#define __MD_H__

#include <iostream>
#include <cstring>
#include "../../h/ThostFtdcMdApi.h"
#include <string>
#include <vector>
#include <hiredis/hiredis.h>
#include <cstdlib>

using namespace std;

extern vector<char*> vec;
extern vector<string> vhq1;
extern vector<string> vhq2;
extern vector<string> *vhq;

extern pthread_mutex_t mutex;

struct args
{
	int insp;
	vector<char*> vecp;
};

class MdSpi : public CThostFtdcMdSpi
{
	public:
		int ins;
		MdSpi(CThostFtdcMdApi *mdApi);
		~MdSpi();
		//建立连接时触发
		virtual void OnFrontConnected();
		//保持连接(自动完成)
		virtual void OnFrontDisconnected(int nReason);
		//登录请求响应
		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		//登出请求响应
		virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		//订阅行情应答
		virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		//取消订阅行情应答
		virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		//深度行情通知
		virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	private:
		CThostFtdcMdApi *mdApi;
		int loginRequestID;
};

#endif
