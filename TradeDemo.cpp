// TradeDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Windows.h"


#include "IEsunnyTrade.h"


int main(int argc, _TCHAR* argv[])
{
	char APPID[]="67338859E3A72F71581A4E022D774963581A4E022D774963581A4E022D774963581A4E022D774963581A4E022D7749635E59";
	char CER[]="C7833C7AE258DB7174AADD371C6BCC7C659DEA0C1BE1425CA76D75D96007A7267AFE4CBF4CAA52FD1EFE57BEF5308F29AD7E88F3DD9C1B223656023D0FEABB6D3C72FB43269F85A7DB6F5A7D9F5031EE30D8D766857003C2581A4E022D774963581A4E022D774963581A4E022D774963581A4E022D774963581A4E022D774963D050C47BED3ED850EB24DD23CBAEB147374BDA8B40E4214C581A4E022D774963581A4E022D774963581A4E022D774963581A4E022D774963581A4E022D77496354E606ACCBE47772";

	
	IEsunnyTrade * pTrade = new IEsunnyTrade(CER,APPID);

	 if(! pTrade->Open("123.15.58.21",7070))
		 return -1;

	Sleep(1000);

	TEsLoginReqField reqLogin;
	memset(&reqLogin,0,sizeof(reqLogin));
	reqLogin.IsCaLogin = NOT_CA_LOGIN;
	reqLogin.Identity =  IDENTITY_CLIENT;
	reqLogin.IsForcePwd = NOT_FORCE_PWD;
	strncpy_s(reqLogin.ClientNo,sizeof(reqLogin.ClientNo),"用户名",sizeof(reqLogin.ClientNo)-1);
	strncpy_s(reqLogin.LoginPwd,sizeof(reqLogin.LoginPwd),"密码",sizeof(reqLogin.LoginPwd)-1);

	int reqID=0;
	if(pTrade->Login(reqLogin,reqID)==0)
	{
		printf("发送登陆指令成功\n");
	}
	else
	{
		printf("发送登陆指令失败\n");
	}

	//等待登陆成功，数据初始化完成
	Sleep(5000);

	//成功登陆，开始下单，定义报单结构体
	TEsOrderInsertReqField req;
	memset(&req,0,sizeof(req));
	//客户号
	strcpy_s(req.ClientNo,"用户名");
	//商品代码
	strcpy_s(req.CommodityNo,"S");
	//合约代码
	strcpy_s(req.ContractNo,"0705");
	//买卖方向
	req.Direct=DIRECT_BUY;
	//开仓平仓
	req.Offset=OFFSET_OPEN;
	//投机保值
	req.Hedge=HEDGE_T;
	//委托类型
	req.OrderType=ORDER_TYPE_LIMIT;
	//是否风险报单
	req.IsRiskOrder=RISK_ORDER_NO;
	//委托模式
	req.OrderMode=ORDER_MODE_GFD;
	//委托方式,单客户不用关注本字段
	req.OrderWay=ORDER_WAY_PROXY_ETRADER;
	//委托价格
	req.OrderPrice=630;
	//委托数量
	req.OrderVol=1;


	int iReqID;

	int ret = pTrade->OrderInsert(req,iReqID);

	if(ret==0)
	{
		printf("发送指令成功\n");
	}
	else
	{
		printf("发送指令失败 err=%d\n",ret);
	}


	
	Sleep(50000);

	return 0;
}

