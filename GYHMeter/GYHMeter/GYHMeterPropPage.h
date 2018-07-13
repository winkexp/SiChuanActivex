#pragma once

// GYHMeterPropPage.h : CGYHMeterPropPage 属性页类的声明。


// CGYHMeterPropPage : 有关实现的信息，请参阅 GYHMeterPropPage.cpp。

class CGYHMeterPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGYHMeterPropPage)
	DECLARE_OLECREATE_EX(CGYHMeterPropPage)

// 构造函数
public:
	CGYHMeterPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_GYHMETER };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

