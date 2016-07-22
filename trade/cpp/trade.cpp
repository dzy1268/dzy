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
	file_hy.open("../conf/hydm", ios::out);
	file_hy.clear();
	file_hy.close();
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
	
	CThostFtdcQryInstrumentField *ord = new CThostFtdcQryInstrumentField();
	tdapi->ReqQryInstrument(ord, 0);
//	tradingDate = tdapi->GetTradingDay();//设置交易日期

/*	CThostFtdcQryTradingAccountField *account = new CThostFtdcQryTradingAccountField();
	strcpy(account->BrokerID, BROKER.c_str());
	strcpy(account->InvestorID, USER_ID.c_str());
	tdapi->ReqQryTradingAccount(account, 999);
*/
//发出报单录入请求
/*        CThostFtdcInputOrderField ord;
        memset(&ord, 0, sizeof(ord));

        strcpy(ord.BrokerID, "9999");
        strcpy(ord.InvestorID, "057213");
        strcpy(ord.InstrumentID, "IH1609");
        strcpy(ord.OrderRef, "000000000001");
        strcpy(ord.UserID, "057213");
        ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        ord.Direction = THOST_FTDC_D_Buy;
        strcpy(ord.CombOffsetFlag, "0");
        strcpy(ord.CombHedgeFlag, "1");
        ord.LimitPrice = 2050;
        ord.VolumeTotalOriginal = 1;
        ord.TimeCondition = THOST_FTDC_TC_GFD;
        strcpy(ord.GTDDate, "");
        ord.VolumeCondition = THOST_FTDC_VC_AV;
        ord.MinVolume = 0;
        ord.ContingentCondition = THOST_FTDC_CC_Immediately;
        ord.StopPrice = 0;
        ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	ord.IsAutoSuspend = 0;
	tdapi->ReqOrderInsert(&ord, 1);
	cout << "1" << endl;
	*/
}

//报单录入应答
void TradeSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	// 输出报单录入结果
//	cout << "2" << endl;
//	printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
}

///报单回报
void TradeSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
//	cout << "3" << endl;
//	printf("OnRtnOrder:\n");
//	printf("OrderSysID=[%s]\n", pOrder->OrderSysID);
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

//请求查询合约响应
void TradeSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	file_hy.open("../conf/hydm", ios::app);
	file_hy << pInstrument->InstrumentID << " ";
	file_hy.close();
//	cout << pInstrument->InstrumentID << endl;
}
