#pragma once

// GYHMeterPropPage.h : CGYHMeterPropPage ����ҳ���������


// CGYHMeterPropPage : �й�ʵ�ֵ���Ϣ������� GYHMeterPropPage.cpp��

class CGYHMeterPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGYHMeterPropPage)
	DECLARE_OLECREATE_EX(CGYHMeterPropPage)

// ���캯��
public:
	CGYHMeterPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_GYHMETER };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

