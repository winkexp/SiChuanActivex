// GYHMeterPropPage.cpp : CGYHMeterPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "GYHMeter.h"
#include "GYHMeterPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGYHMeterPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CGYHMeterPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CGYHMeterPropPage, "GYHMETER.GYHMeterPropPage.1",
	0x396285fd, 0x88c2, 0x42d2, 0xab, 0x5a, 0xbe, 0xe9, 0xdb, 0x8d, 0x3a, 0x5f)



// CGYHMeterPropPage::CGYHMeterPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CGYHMeterPropPage ��ϵͳע�����

BOOL CGYHMeterPropPage::CGYHMeterPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GYHMETER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGYHMeterPropPage::CGYHMeterPropPage - ���캯��

CGYHMeterPropPage::CGYHMeterPropPage() :
	COlePropertyPage(IDD, IDS_GYHMETER_PPG_CAPTION)
{
}



// CGYHMeterPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CGYHMeterPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGYHMeterPropPage ��Ϣ�������
