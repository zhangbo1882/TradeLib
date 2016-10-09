// TradeDemo.cpp : �������̨Ӧ�ó������ڵ㡣
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
	strncpy_s(reqLogin.ClientNo,sizeof(reqLogin.ClientNo),"�û���",sizeof(reqLogin.ClientNo)-1);
	strncpy_s(reqLogin.LoginPwd,sizeof(reqLogin.LoginPwd),"����",sizeof(reqLogin.LoginPwd)-1);

	int reqID=0;
	if(pTrade->Login(reqLogin,reqID)==0)
	{
		printf("���͵�½ָ��ɹ�\n");
	}
	else
	{
		printf("���͵�½ָ��ʧ��\n");
	}

	//�ȴ���½�ɹ������ݳ�ʼ�����
	Sleep(5000);

	//�ɹ���½����ʼ�µ������屨���ṹ��
	TEsOrderInsertReqField req;
	memset(&req,0,sizeof(req));
	//�ͻ���
	strcpy_s(req.ClientNo,"�û���");
	//��Ʒ����
	strcpy_s(req.CommodityNo,"S");
	//��Լ����
	strcpy_s(req.ContractNo,"0705");
	//��������
	req.Direct=DIRECT_BUY;
	//����ƽ��
	req.Offset=OFFSET_OPEN;
	//Ͷ����ֵ
	req.Hedge=HEDGE_T;
	//ί������
	req.OrderType=ORDER_TYPE_LIMIT;
	//�Ƿ���ձ���
	req.IsRiskOrder=RISK_ORDER_NO;
	//ί��ģʽ
	req.OrderMode=ORDER_MODE_GFD;
	//ί�з�ʽ,���ͻ����ù�ע���ֶ�
	req.OrderWay=ORDER_WAY_PROXY_ETRADER;
	//ί�м۸�
	req.OrderPrice=630;
	//ί������
	req.OrderVol=1;


	int iReqID;

	int ret = pTrade->OrderInsert(req,iReqID);

	if(ret==0)
	{
		printf("����ָ��ɹ�\n");
	}
	else
	{
		printf("����ָ��ʧ�� err=%d\n",ret);
	}


	
	Sleep(50000);

	return 0;
}

