#pragma once

// GYHMeterCtrl.h : CGYHMeterCtrl ActiveX 控件类的声明。
#include "CameraDlg.h"
#include "GyReader.h"
#include "HDKeyboard.h"

// CGYHMeterCtrl : 有关实现的信息，请参阅 GYHMeterCtrl.cpp。

class CGYHMeterCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGYHMeterCtrl)

// 构造函数
public:
	CGYHMeterCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CGYHMeterCtrl();

	DECLARE_OLECREATE_EX(CGYHMeterCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CGYHMeterCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGYHMeterCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CGYHMeterCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidiReadIdentityCard = 46L,
		dispidiReadICCardNum = 45L,
		dispidiDoDebit_HSM_Step2 = 44L,
		dispidiDoDebit_HSM_Step1 = 43L,
		dispidiUnblockPIN_HSM_Step3 = 42L,
		dispidiUnblockPIN_HSM_Step2 = 41L,
		dispidiUnblockPIN_HSM_Step1 = 40L,
		dispidiReloadPIN_HSM_Step3 = 39L,
		dispidiReloadPIN_HSM_Step2 = 38L,
		dispidiReloadPIN_HSM_Step1 = 37L,
		dispidiWriteCard_HSM_Step2 = 36L,
		dispidiWriteCard_HSM_Step1 = 35L,
		dispidiReadCard_HSM_Step2 = 34L,
		dispidiReadCard_HSM_Step1 = 33L,
		dispidiReadCardBas_HSM_Step2 = 32L,
		dispidiReadCardBas_HSM_Step1 = 31L,
		dispidiReadDebitRecord = 30L,
		dispidiDoDebit = 29L,
		dispidiUnblockPIN = 28L,
		dispidiReloadPIN = 27L,
		dispidiChangePIN = 26L,
		dispidiVerifyPIN = 25L,
		dispidiWriteCard = 24L,
		dispidiReadCard = 23L,
		dispidiReadCardBas = 22L,
		dispidSS_CMR_ReadBarcodeAB = 21L,
		dispidSS_Base64StringAB = 20L,
		dispidSS_CMR_WaterMarkSet = 19L,
		dispidSS_CMR_WaterMarkAddAB = 18L,
		dispidSS_CMR_SetCutModeAB = 17L,
		dispidSS_CMR_ParaSetAB = 16L,
		dispidSS_CMR_ShowVideoPropAB = 15L,
		dispidSS_CMR_StopTimerCapAB = 14L,
		dispidSS_CMR_StartTimerCapAB = 13L,
		dispidSS_CMR_VideoStopAB = 12L,
		dispidSS_CMR_VideoStartAB = 11L,
		dispidSS_CMR_RotateRight = 10L,
		dispidSS_CMR_RotateLeftAB = 9L,
		dispidSS_CMR_ZoomOutAB = 8L,
		dispidSS_CMR_ZoomInAB = 7L,
		dispidSS_CMR_PhotoAB = 6L,
		dispidSS_CMR_GetStatusAB = 5L,
		dispidSS_CMR_CloseSideAB = 4L,
		dispidSS_CMR_OpenSideAB = 3L,
		dispidSS_CMR_CloseAB = 2L,
		dispidSS_CMR_OpenAB = 1L
	};
protected:
	LONG SS_CMR_OpenAB(LONG iCamNo, LONG mainX, LONG mainY, LONG mwidth, LONG mheight, LONG sideX, LONG sideY, LONG widthside, LONG heightside);
	LONG SS_CMR_CloseAB(LONG iCamNo);
	LONG SS_CMR_OpenSideAB(LONG iCamNoSide);
	LONG SS_CMR_CloseSideAB(LONG iCamNoSide);
	BSTR SS_CMR_GetStatusAB(LONG iCamNo);
	LONG SS_CMR_PhotoAB(LONG iCamNo, LPCTSTR fileAddr);
	LONG SS_CMR_ZoomInAB(LONG iCamNo);
	LONG SS_CMR_ZoomOutAB(LONG iCamNo);
	LONG SS_CMR_RotateLeftAB(LONG iCamNo);
	LONG SS_CMR_RotateRight(LONG iCamNo);
	LONG SS_CMR_VideoStartAB(LONG iCamNo, LPCTSTR fileAddr);
	LONG SS_CMR_VideoStopAB(LONG iCamNo, LPCTSTR fileAddr);
	LONG SS_CMR_StartTimerCapAB(LONG iCamNo, LONG nTime, LPCTSTR pImagePath);
	LONG SS_CMR_StopTimerCapAB(LONG iCamNo);
	LONG SS_CMR_ShowVideoPropAB(LONG iCamNo);
	LONG SS_CMR_ParaSetAB(LONG iCamNo);
	LONG SS_CMR_SetCutModeAB(LONG iCamNo, LONG CutMode);
	LONG SS_CMR_WaterMarkAddAB(LONG iCamNo);
	LONG SS_CMR_WaterMarkSet(LONG iCamNo);
	BSTR SS_Base64StringAB(LONG iCamNo);
	BSTR SS_CMR_ReadBarcodeAB(LONG iCamNo);
	BSTR iReadCardBas(LONG iType);
	BSTR iReadCard(LONG iType, LONG iAuthType, LPCTSTR pCardInfo, LPCTSTR pFileAddr);
	BSTR iWriteCard(LONG iType, LPCTSTR pCardInfo, LPCTSTR pFileAddr, LPCTSTR pWriteData);
	BSTR iVerifyPIN(LONG iType);
	BSTR iChangePIN(LONG iType);
	BSTR iReloadPIN(LONG iType, LPCTSTR pCardInfo);
	BSTR iUnblockPIN(LONG iType, LPCTSTR pCardInfo);
	BSTR iDoDebit(LONG iType, LPCTSTR pCardInfo, LPCTSTR pPayInfo);
	BSTR iReadDebitRecord(LONG iType);
	BSTR iReadCardBas_HSM_Step1(LONG iType);
	BSTR iReadCardBas_HSM_Step2(LPCTSTR pKey);
	BSTR iReadCard_HSM_Step1(LONG iType, LPCTSTR pCardInfo, LPCTSTR pFileAddr);
	BSTR iReadCard_HSM_Step2(LPCTSTR pKey);
	BSTR iWriteCard_HSM_Step1(LONG iType, LPCTSTR pCardInfo, LPCTSTR pFileAddr);
	BSTR iWriteCard_HSM_Step2(LPCTSTR pKey, LPCTSTR pWriteData);
	BSTR iReloadPIN_HSM_Step1(LONG iType, LPCTSTR pCardInfo);
	BSTR iReloadPIN_HSM_Step2(LPCTSTR pKey);
	BSTR iReloadPIN_HSM_Step3(LPCTSTR pKey);
	BSTR iUnblockPIN_HSM_Step1(LONG iType, LPCTSTR pCardInfo);
	BSTR iUnblockPIN_HSM_Step2(LPCTSTR pKey);
	BSTR iUnblockPIN_HSM_Step3(LPCTSTR pKey);
	BSTR iDoDebit_HSM_Step1(LONG iType, LPCTSTR pCardInfo, LPCTSTR pPayInfo);
	BSTR iDoDebit_HSM_Step2(LPCTSTR pKey);


	/************************************************************************/
	/* 高拍仪                                                                     */
	/************************************************************************/	
	CCameraDlg mainDlg;
	HWND mainHwnd;
	BOOL mainOpen;

	CCameraDlg subDlg;
	HWND subHwnd;
	BOOL subOpen;

	VOID (*fIdCard)(ULONG_PTR);

	GyReader* reader;
	HANDLE devNo;
	HDKeyboard keyboard;
	CString flag;//算法标示
	CString outStr;
public:
//	afx_msg void OnPaint();
protected:
	BSTR iReadICCardNum(void);
	BSTR iReadIdentityCard(void);
};

