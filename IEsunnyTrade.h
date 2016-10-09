
#pragma once 


#include "EsunnyForeignApi.h"

#pragma comment(lib,"ForeignTradeApi.lib")

using namespace ESForeign;

class IEsunnyTrade:public IEsunnyTradeSpi
{

private :
	IEsunnyTradeApi * Tap_Api;	

public:
	IEsunnyTrade(char * pCertKey,char * pApplication)
	{
		TEsCertInfoType CertKey;

		int CreateErrorCode;

		TEsLogPathType LogFilePath;

		TEsAppIDType ApplicationID;

		strncpy_s(CertKey,sizeof(CertKey),pCertKey,sizeof(CertKey)-1);

		strncpy_s(LogFilePath,sizeof(LogFilePath),".",sizeof(LogFilePath)-1);
	
		strncpy_s(ApplicationID,sizeof(ApplicationID),pApplication,sizeof(ApplicationID)-1);


		Tap_Api=CreateEsunnyForeignTradeApi(CertKey,&CreateErrorCode,LogFilePath,ApplicationID);

		if(Tap_Api != NULL) Tap_Api->SetSpi(this);

	}

	~IEsunnyTrade()
	{
		DelEsunnyForeignTradeApi(Tap_Api);
	}



	//建立连接
	bool Open(TEsAddressField& connect)
	{
		TEsAddressField pData;
		strncpy_s(pData.Ip,sizeof(pData.Ip),connect.Ip,sizeof(pData.Ip)-1);
		pData.Port = connect.Port;
		if(!Tap_Api) return false;
		return Tap_Api->Open(pData);
	}

	bool Open(char * ip , int port)
	{
		TEsAddressField pData;
		strncpy_s(pData.Ip,sizeof(pData.Ip),ip,sizeof(pData.Ip)-1);
		pData.Port = port;
		if(!Tap_Api) return false;
		return Tap_Api->Open(pData);
	}

	//登陆
	int Login(const TEsLoginReqField& req,int &iReqID)
	{
		return  Tap_Api->Login(req,iReqID);
	}
	
	//关闭与服务器的连接
	void Close()
	{
		Tap_Api->Close();
	}

	//调用登出的函数
	int CLogout(int& iReqID)
	{
		int a = Tap_Api->LogOut(iReqID);
		Tap_Api ->Close();
		return a;
	}

	//下单
	int OrderInsert(const TEsOrderInsertReqField& req, int& iReqID)
	{
		return Tap_Api->OrderInsert(req,iReqID);
	}







public:

    
	    virtual void __cdecl OnOpen() {}

		virtual void __cdecl OnClose(){}

     
		virtual void __cdecl OnLogin(const TEsLoginRspField* rsp, int errCode, const int iReqID) {

			if(errCode==0)
			{
				printf("登陆号:%s  登陆用户=%s\n",rsp->LoginNo,rsp->LoginName);
			}else
			{
				printf("登陆失败 错误码=%d",errCode);
			}
		
		
		}

    
		virtual void __cdecl OnInitFinished(int errCode) {

			printf("初始化数据完成\n");
		}

		virtual void __cdecl OnLogOut(int errCode, const int iReqID) {
			
			
		}

 
        virtual void __cdecl OnRspSetPassword(const TEsClientPasswordModifyRspField* rsp, int errCode, const int iReqID){}

        virtual void __cdecl OnRspSetOperPassword(const TEsOperatorPasswordModifyRspField* rsp, int errCode, const int iReqID) {}


        virtual void __cdecl OnQryMoney(const TEsMoneyQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

        virtual void __cdecl OnRtnMoney(const TEsMoneyChgNoticeField& rsp) {}

        virtual void __cdecl OnRspCashOperQry(const TEsCashOperQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}
        
        
        virtual void __cdecl OnRspCashOper(const TEsCashOperRspField* rsp, int errCode, const int iReqID) {

		
		}
      
        virtual void __cdecl OnRtnCashOper(const TEsCashOperNoticeField& rsp) {

		}
    
    
        virtual void __cdecl OnRspCashCheck(const TEsCashCheckRspField* rsp, int errCode, const int iReqID) {
		}
        

        virtual void __cdecl OnRtnCashCheck(const TEsCashCheckNoticeField& rsp) {}

        virtual void __cdecl OnRspCashAdjustQry(const TEsAdjustQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

		virtual void __cdecl OnRspOrderInsert(const TEsOrderInsertRspField* rsp, int errCode, const int iReqID) {
		
			if (errCode == 0)
			{

				printf(" OrderInsert 回报 \n" );

			}else
			{

				printf("OrderInsert 错误码=%d\n",errCode);

			}
		}

		virtual void __cdecl OnRspOrderModify(const TEsOrderModifyRspField* rsp, int errCode, const int iReqID){}

		virtual void __cdecl OnRspOrderDelete(const TEsOrderDeleteRspField* rsp, int errCode, const int iReqID) {}
        
        virtual void __cdecl OnRspQryOrder(const TEsOrderDataQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}
        
        virtual void __cdecl OnRspHistOrderQry(const TEsHisOrderQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}
        
		virtual void __cdecl OnRtnOrderState(const TEsOrderStateNoticeField& rsp) {}
    
		virtual void __cdecl OnRtnOrderInfo(const TEsOrderInfoNoticeField& rsp) {}

 
        virtual void __cdecl OnRspMatchQry(const TEsMatchDataQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

		virtual void __cdecl OnRtnMatchState(const TEsMatchStateNoticeField& rsp) {}


		virtual void __cdecl OnRtnMatchInfo(const TEsMatchInfoNoticeField& rsp) {}


        virtual void __cdecl OnRspHistMatchQry(const TEsHisMatchQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

        virtual void __cdecl OnQryHold(const TEsHoldQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

        virtual void __cdecl OnRtnHold(const TEsHoldQryRspField& rsp) {}


        virtual void __cdecl OnQryExchangeState(const TEsExchangeQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

		virtual void __cdecl OnRtnExchangeState(const TEsExchangeStateModifyNoticeField& rsp) {}

        virtual void __cdecl OnQryCommodity(const TEsCommodityQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

        virtual void __cdecl OnQryContract(const TEsContractQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}


        virtual void __cdecl OnQryClient(const TEsOperatorClientQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

        virtual void __cdecl OnRspHistCashOperQry(const TEsHisCashOperQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

        virtual void __cdecl OnRspHistCashAdjustQry(const TEsHisAdjustQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

        
        virtual void __cdecl OnRspAuthClient(const TEsClientPasswordAuthRspField* rsp, int errCode, const int iReqID) {}

        virtual void __cdecl OnRspQryCurrency(const TEsCurrencyQryRspField* rsp, TEsIsLastType islast, int errCode, const int iReqID) {}

        virtual void __cdecl OnRtnExchangeRateMod(const TEsExchangeRateModifyNoticeField& rsp) {}

        virtual void __cdecl OnRtnOrderRemove(const TEsOrderRemoveNoticeField& rsp) {}

        virtual void __cdecl OnRtnMatchRemove(const TEsMatchRemoveNoticeField& rsp) {}


        virtual void __cdecl OnRtnCommodityState(const TEsCommodityStateModNoticeField& rsp) {}


        virtual void __cdecl OnRtnContractAdd(const TEsContractAddNoticeField& rsp) {}

};