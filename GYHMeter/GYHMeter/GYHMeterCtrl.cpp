// GYHMeterCtrl.cpp : CGYHMeterCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "GYHMeter.h"
#include "GYHMeterCtrl.h"
#include "GYHMeterPropPage.h"
#include "afxdialogex.h"
#include "GyReader.h"
#include "MwReader.h"
#include "HDKeyboard.h"


//�õ�����ch֮����ַ���,�����ڶ���ch���±귵�ظ�firstindex ��Ϊ�´�ʹ�õĿ�ʼ
//�±��0��ʼ
CString GetDataItem(int &firstindex,char ch,const CString& CFileline)
{
	CString DataItem;
	int secondindex = 0;

	secondindex = CFileline.Find(ch,firstindex+1);

	if(firstindex==0)
	{
		DataItem = CFileline.Left(secondindex);
	}
	else
	{
		if(secondindex != -1)
		{
			DataItem = CFileline.Mid(firstindex+1,secondindex-firstindex-1);
			/*			DataItem.Remove(' ');*/
		}
		else
		{
			return L"";
		}
	}
	firstindex = secondindex;

	return DataItem;
}

//���ڶ�ȡ��'|'�ָ���һ������
void GetString(const CString& CFileLine, CStringArray& dest ,char schar)
{
	CString Ctmp = CFileLine;
	int icount = Ctmp.Replace(schar,'<');

	int index = 0;

	for(int i=0;i<icount;i++)
	{
		dest.Add(GetDataItem(index,schar,CFileLine));
	}	
	dest.Add(CFileLine.Right(CFileLine.GetLength()-index-1));
}



//����ͷ��: 0: ��������ͷ	1: ��Ա����ͷ 2: �ͻ�����ͷ
int selectCam(int index)
{
	int ret = 0;
	switch (index)
	{
	case 0:
		ret = 1;
		break;
	case 1:
		ret = 0;
		break;
	case 2:
		ret = 0;
		break;
	default:
		break;
	}
	return ret;
}


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGYHMeterCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CGYHMeterCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
//	ON_WM_PAINT()
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CGYHMeterCtrl, COleControl)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_OpenAB", dispidSS_CMR_OpenAB, SS_CMR_OpenAB, VT_I4, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_CloseAB", dispidSS_CMR_CloseAB, SS_CMR_CloseAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_OpenSideAB", dispidSS_CMR_OpenSideAB, SS_CMR_OpenSideAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_CloseSideAB", dispidSS_CMR_CloseSideAB, SS_CMR_CloseSideAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_GetStatusAB", dispidSS_CMR_GetStatusAB, SS_CMR_GetStatusAB, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_PhotoAB", dispidSS_CMR_PhotoAB, SS_CMR_PhotoAB, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_ZoomInAB", dispidSS_CMR_ZoomInAB, SS_CMR_ZoomInAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_ZoomOutAB", dispidSS_CMR_ZoomOutAB, SS_CMR_ZoomOutAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_RotateLeftAB", dispidSS_CMR_RotateLeftAB, SS_CMR_RotateLeftAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_RotateRight", dispidSS_CMR_RotateRight, SS_CMR_RotateRight, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_VideoStartAB", dispidSS_CMR_VideoStartAB, SS_CMR_VideoStartAB, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_VideoStopAB", dispidSS_CMR_VideoStopAB, SS_CMR_VideoStopAB, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_StartTimerCapAB", dispidSS_CMR_StartTimerCapAB, SS_CMR_StartTimerCapAB, VT_I4, VTS_I4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_StopTimerCapAB", dispidSS_CMR_StopTimerCapAB, SS_CMR_StopTimerCapAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_ShowVideoPropAB", dispidSS_CMR_ShowVideoPropAB, SS_CMR_ShowVideoPropAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_ParaSetAB", dispidSS_CMR_ParaSetAB, SS_CMR_ParaSetAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_SetCutModeAB", dispidSS_CMR_SetCutModeAB, SS_CMR_SetCutModeAB, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_WaterMarkAddAB", dispidSS_CMR_WaterMarkAddAB, SS_CMR_WaterMarkAddAB, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_WaterMarkSet", dispidSS_CMR_WaterMarkSet, SS_CMR_WaterMarkSet, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_Base64StringAB", dispidSS_Base64StringAB, SS_Base64StringAB, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "SS_CMR_ReadBarcodeAB", dispidSS_CMR_ReadBarcodeAB, SS_CMR_ReadBarcodeAB, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadCardBas", dispidiReadCardBas, iReadCardBas, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadCard", dispidiReadCard, iReadCard, VT_BSTR, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iWriteCard", dispidiWriteCard, iWriteCard, VT_BSTR, VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iVerifyPIN", dispidiVerifyPIN, iVerifyPIN, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iChangePIN", dispidiChangePIN, iChangePIN, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReloadPIN", dispidiReloadPIN, iReloadPIN, VT_BSTR, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iUnblockPIN", dispidiUnblockPIN, iUnblockPIN, VT_BSTR, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iDoDebit", dispidiDoDebit, iDoDebit, VT_BSTR, VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadDebitRecord", dispidiReadDebitRecord, iReadDebitRecord, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadCardBas_HSM_Step1", dispidiReadCardBas_HSM_Step1, iReadCardBas_HSM_Step1, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadCardBas_HSM_Step2", dispidiReadCardBas_HSM_Step2, iReadCardBas_HSM_Step2, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadCard_HSM_Step1", dispidiReadCard_HSM_Step1, iReadCard_HSM_Step1, VT_BSTR, VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadCard_HSM_Step2", dispidiReadCard_HSM_Step2, iReadCard_HSM_Step2, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iWriteCard_HSM_Step1", dispidiWriteCard_HSM_Step1, iWriteCard_HSM_Step1, VT_BSTR, VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iWriteCard_HSM_Step2", dispidiWriteCard_HSM_Step2, iWriteCard_HSM_Step2, VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReloadPIN_HSM_Step1", dispidiReloadPIN_HSM_Step1, iReloadPIN_HSM_Step1, VT_BSTR, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReloadPIN_HSM_Step2", dispidiReloadPIN_HSM_Step2, iReloadPIN_HSM_Step2, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReloadPIN_HSM_Step3", dispidiReloadPIN_HSM_Step3, iReloadPIN_HSM_Step3, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iUnblockPIN_HSM_Step1", dispidiUnblockPIN_HSM_Step1, iUnblockPIN_HSM_Step1, VT_BSTR, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iUnblockPIN_HSM_Step2", dispidiUnblockPIN_HSM_Step2, iUnblockPIN_HSM_Step2, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iUnblockPIN_HSM_Step3", dispidiUnblockPIN_HSM_Step3, iUnblockPIN_HSM_Step3, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iDoDebit_HSM_Step1", dispidiDoDebit_HSM_Step1, iDoDebit_HSM_Step1, VT_BSTR, VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iDoDebit_HSM_Step2", dispidiDoDebit_HSM_Step2, iDoDebit_HSM_Step2, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadICCardNum", dispidiReadICCardNum, iReadICCardNum, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CGYHMeterCtrl, "iReadIdentityCard", dispidiReadIdentityCard, iReadIdentityCard, VT_BSTR, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CGYHMeterCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CGYHMeterCtrl, 1)
	PROPPAGEID(CGYHMeterPropPage::guid)
END_PROPPAGEIDS(CGYHMeterCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CGYHMeterCtrl, "GYHMETER.GYHMeterCtrl.1",
	0x7ee63763, 0x4324, 0x4a8b, 0xb4, 0x89, 0x25, 0x11, 0x29, 0x1e, 0x40, 0xe3)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CGYHMeterCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID IID_DGYHMeter = { 0x935E56A4, 0x90EC, 0x44F9, { 0x8E, 0x4D, 0x1B, 0xA7, 0xCE, 0x25, 0x60, 0xF8 } };
const IID IID_DGYHMeterEvents = { 0xCBC48A8E, 0x86F4, 0x45B5, { 0xAD, 0xD3, 0xCA, 0xD4, 0x51, 0xA5, 0xA4, 0x61 } };


// �ؼ�������Ϣ

static const DWORD _dwGYHMeterOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGYHMeterCtrl, IDS_GYHMETER, _dwGYHMeterOleMisc)



// CGYHMeterCtrl::CGYHMeterCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CGYHMeterCtrl ��ϵͳע�����

BOOL CGYHMeterCtrl::CGYHMeterCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_GYHMETER,
			IDB_GYHMETER,
			afxRegApartmentThreading,
			_dwGYHMeterOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGYHMeterCtrl::CGYHMeterCtrl - ���캯��

CGYHMeterCtrl::CGYHMeterCtrl()
{
	InitializeIIDs(&IID_DGYHMeter, &IID_DGYHMeterEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�

	/************************************************************************/
	/* ������                                                                     */
	/************************************************************************/
	//mainDlg = NULL;
	mainHwnd = NULL;
	mainOpen = FALSE;

	//subDlg = NULL;
	subHwnd = NULL;
	subOpen = FALSE;

	devNo = NULL;
	reader = new MwReader();
}



// CGYHMeterCtrl::~CGYHMeterCtrl - ��������

CGYHMeterCtrl::~CGYHMeterCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ������
	if (mainOpen)
	{
		SS_CMR_CloseAB(0);
	}
	mainHwnd = NULL;
	mainOpen = FALSE;
	subHwnd = NULL;
	subOpen = FALSE;
	subDlg.DestroyWindow();
	mainDlg.DestroyWindow();
}



// CGYHMeterCtrl::OnDraw - ��ͼ����

void CGYHMeterCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
}



// CGYHMeterCtrl::DoPropExchange - �־���֧��

void CGYHMeterCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CGYHMeterCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CGYHMeterCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CGYHMeterCtrl::AboutBox - ���û���ʾ�����ڡ���

void CGYHMeterCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GYHMETER);
	dlgAbout.DoModal();
}



// CGYHMeterCtrl ��Ϣ�������


LONG CGYHMeterCtrl::SS_CMR_OpenAB(LONG iCamNo, LONG mainX, LONG mainY, LONG mwidth, LONG mheight, LONG sideX, LONG sideY, LONG widthside, LONG heightside)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������	

	HINSTANCE hOcx = ::GetModuleHandle(L"GYHMeter.ocx"); 
	CString strPath; 
	::GetModuleFileNameW(hOcx, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int index = strPath.ReverseFind('\\');
	strPath = strPath.Mid(0, index + 1);
	SetCurrentDirectory(strPath);

	//������ͷ
	iCamNo = selectCam(iCamNo);
	//mainDlg = new CCameraDlg();	
	if (!mainHwnd)
	{
		mainDlg.Create(IDD_DIALOG1, this);
	}
	
	mainDlg.MoveWindow(mainX, mainY, mwidth, mheight);	
	mainDlg.ShowWindow(SW_SHOWNORMAL);
	mainHwnd = mainDlg.GetDlgItem(IDC_STATIC)->m_hWnd;

	BOOL ret = ZZOpenDeviceEx(mainHwnd, iCamNo);
	if (!ret)
	{		
		return -1;
	}
	ret = ZZOpenVideo(mainHwnd);
	if (!ret)
	{		
		ZZCloseDevice(mainHwnd);
		return -2;
	}	

	//������ͷ
	if (!(sideX == 0 && sideY == 0 && widthside == 0 && heightside == 0))
	{
		if (!subHwnd)
		{
			subDlg.Create(IDD_DIALOG1, this);
		}
			
		subDlg.MoveWindow(sideX, sideY, widthside, heightside);	
		subDlg.ShowWindow(SW_SHOWNORMAL);
		subHwnd = subDlg.GetDlgItem(IDC_STATIC)->m_hWnd;

		ret = ZZOpenDeviceEx(subHwnd, 0);
		if (!ret)
		{		
			return -1;
		}
		ret = ZZOpenVideo(subHwnd);
		if (!ret)
		{		
			ZZCloseDevice(subHwnd);
			return -2;
		}	
		subOpen = TRUE;
	}	
	mainOpen = TRUE;	
	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_CloseAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	if (subOpen)
	{
		if (!ZZCloseVideo(subHwnd))
		{
			return -1;
		}
		if (!ZZCloseDevice(subHwnd))
		{
			return -2;
		}		
		subOpen = FALSE;
		//subDlg.ShowWindow(SW_HIDE);
	}

	if (mainOpen)
	{
		if (!ZZCloseVideo(mainHwnd))
		{
			return -1;
		}
		if (!ZZCloseDevice(mainHwnd))
		{
			return -2;
		}		
		mainOpen = FALSE;		
		//mainDlg.ShowWindow(SW_HIDE);		
	}

	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_OpenSideAB(LONG iCamNoSide)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	if (mainHwnd == NULL)
	{
		return -1;
	}
	iCamNoSide = selectCam(iCamNoSide);
	BOOL ret = ZZOpenDeviceEx(subHwnd, iCamNoSide);
	if (!ret)
	{		
		return -1;
	}
	ret = ZZOpenVideo(subHwnd);
	if (!ret)
	{		
		ZZCloseDevice(subHwnd);
		return -2;
	}	
	subOpen = TRUE;
	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_CloseSideAB(LONG iCamNoSide)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	if (subOpen)
	{
		if (!ZZCloseVideo(subHwnd))
		{
			return -1;
		}
		if (!ZZCloseDevice(subHwnd))
		{
			return -2;
		}		
		
		subOpen = FALSE;
	}	
	return 0;
}


BSTR CGYHMeterCtrl::SS_CMR_GetStatusAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������

	if (iCamNo == 0)
	{
		if (mainOpen)
		{
			strResult = L"�豸���ڴ�״̬";
		}else{
			strResult = L"�豸���ڹر�״̬";
		}
	}else if (iCamNo == 1 || iCamNo == 2)
	{
		if (subOpen)
		{
			strResult = L"�豸���ڴ�״̬";
		}else{
			strResult = L"�豸���ڹر�״̬";
		}
	}	
	return strResult.AllocSysString();
}


LONG CGYHMeterCtrl::SS_CMR_PhotoAB(LONG iCamNo, LPCTSTR fileAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	CString fileName(fileAddr);

	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}
	if (!ZZCapture(tmp, fileName))
	{
		return -1;
	}	
	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_ZoomInAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}

	if (!ZZSetZoomIn(tmp))
	{
		return -1;
	}

	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_ZoomOutAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}	

	if (!ZZSetZoomOut(tmp))
	{
		return -1;
	}	

	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_RotateLeftAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}
	if (!ZZRotateLeft(tmp))
	{
		return -1;
	}		

	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_RotateRight(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}
	if (!ZZRotateRight(tmp))
	{
		return -1;
	}

	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_VideoStartAB(LONG iCamNo, LPCTSTR fileAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	CString fileName(fileAddr);
	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}
	BOOL flag = ZZStartRecord(tmp, fileName, 400000, 15);
	if (!flag)
	{		
		return -1;
	}	

	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_VideoStopAB(LONG iCamNo, LPCTSTR fileAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}
	BOOL flag = ZZStopRecord(tmp);
	if (!flag)
	{		
		return -1;
	}
	return 0;
}

HWND timerCamno = NULL;
CString timerFileName;
int timerFlag = 10;
//�ص�����
void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
{
	CString link;
	switch(nTimerid)
	{      

	case 100:
		// ����IDΪ1�Ķ�ʱ�����¼�		
		link.Format(L"%s%d.jpg", timerFileName, timerFlag++);
		ZZCapture(timerCamno, link);
		break; 
	default: 
		break;
	}
}    

LONG CGYHMeterCtrl::SS_CMR_StartTimerCapAB(LONG iCamNo, LONG nTime, LPCTSTR pImagePath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	CString tmp(pImagePath);
	timerFileName = tmp;	
	if (iCamNo == 0)
	{
		timerCamno = mainHwnd;
	}else{
		timerCamno = subHwnd;
	}

	::SetTimer(timerCamno, 100, 1000 * nTime, TimerProc);	
	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_StopTimerCapAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	::KillTimer(timerCamno, 100);
	timerCamno = NULL;
	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_ShowVideoPropAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}
	BOOL flag = ZZShowFilter(tmp);
	if (!flag)
	{		
		return -1;
	}
	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_ParaSetAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_SetCutModeAB(LONG iCamNo, LONG CutMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}
	int ret = 0;
	if (iCamNo == 0)
	{
		if (!ZZUnDeskew(tmp))
		{
			ret = VARIANT_FALSE;
		}		
	}else if (iCamNo == 1)
	{
		if (!ZZDeskew(tmp))
		{
			ret = VARIANT_FALSE;
		}		
	}else if (iCamNo == 2)
	{
		if (!ZZMultiDeskew(tmp))
		{
			ret = VARIANT_FALSE;
		}		
	}
	return ret;
}


LONG CGYHMeterCtrl::SS_CMR_WaterMarkAddAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	CString str = L"�����͸�����";
	if (!ZZEnableWatermark(mainHwnd, str, 255, 4))
	{
		return -1;
	}	
	return 0;
}


LONG CGYHMeterCtrl::SS_CMR_WaterMarkSet(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	if (!ZZDisableWatermark(mainHwnd))
	{
		return -1;
	}
	return 0;
}


BSTR CGYHMeterCtrl::SS_Base64StringAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	

	// TODO: �ڴ���ӵ��ȴ���������
	HWND tmp = NULL;
	if (iCamNo == 0)
	{
		tmp = mainHwnd;
	}else{
		tmp = subHwnd;
	}
	BSTR result = ZZCaptureToBase64(tmp);
	CString strResult(result);
	ZZReleaseString(result);	
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::SS_CMR_ReadBarcodeAB(LONG iCamNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	BSTR barcode = ZZGetBarcodeResultEx(strResult);	
	strResult=barcode;
	//strcpy(info, W2A(barcodeStr.GetBuffer(0)));
	ZZReleaseString(barcode);
	return strResult.AllocSysString();
}


//д��־
void WriteLogStr(CString log, int lastErr=0)
{
	USES_CONVERSION;

	HINSTANCE hOcx = ::GetModuleHandle(L"GYHMeter.ocx"); 
	CString strPath; 
	::GetModuleFileNameW(hOcx, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int index = strPath.ReverseFind('\\');
	strPath = strPath.Mid(0, index + 1);
	SetCurrentDirectory(strPath);

	SYSTEMTIME  sysTime;
	//GetSystemTime(&sysTime);
	GetLocalTime(&sysTime);

	char ctime[64]; memset(ctime, 0, 64);

	sprintf(ctime, (("%02d:%02d:%02d:%03d")), sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);

	CString  curTime = CString(ctime);

	memset(ctime, 0, 64);
	sprintf(ctime, (("%04d-%02d-%02d")), sysTime.wYear, sysTime.wMonth, sysTime.wDay);

	CString  fileName;
	fileName.Format(L"%s.log", A2T(ctime));

	FILE* hfile = NULL;	
	hfile = fopen(T2A(fileName), "at+");
	if (hfile)
	{
		fseek(hfile, 0, SEEK_END);
		fprintf(hfile, ("%s: %s\n"), T2A(curTime), T2A(log));
		fclose(hfile);
	}
}

BSTR CGYHMeterCtrl::iReadCardBas(LONG iType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������	
	
	devNo = NULL;	
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"iReadCardBas�򿪶�д��ʧ��";
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//�����Ƿ���PSAM��
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 1, infoATR, &atrLen);
	if (ret != 0)
	{	
		outStr = L"��ⲻ��PSAM��";		
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();		
	}
	reader->CloseReader(devNo);
	devNo = NULL;	
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReadCard(LONG iType, LONG iAuthType, LPCTSTR pCardInfo, LPCTSTR pFileAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	devNo = NULL;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{	
		outStr = L"�򿪶�д��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}

	//�����Ƿ���PSAM��	
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 1, infoATR, &atrLen);
	if (ret != 0)
	{		
		outStr = L"iReadCard��ⲻ��PSAM��";		
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();				
	}	

	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iWriteCard(LONG iType, LPCTSTR pCardInfo, LPCTSTR pFileAddr, LPCTSTR pWriteData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	devNo = NULL;
	if (iType == 2)
	{			
		outStr = L"Ѱ��ʧ��";
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";		
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//�����Ƿ���PSAM��
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 1, infoATR, &atrLen);
	if (ret != 0)
	{	
		outStr = L"iWriteCard��ⲻ��PSAM��";		
		WriteLogStr(outStr);		
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iVerifyPIN(LONG iType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	devNo = NULL;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}
	
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";		
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//��Ƭ��λ 
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 0, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"iVerifyPIN��λ��Ƭʧ��";		
		WriteLogStr(outStr);		
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//ѡ���籣����
	CString cmd = CString("00A404000F7378312E73682EC9E7BBE1B1A3D5CF");	
	char respData[1024] = {0};	
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"iVerifyPINѡ���籣����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	//��ȡ��һ����������
	int readerHandle = keyboard.Keyboard_Open("USB1");
	if (readerHandle <= 0)
	{
		outStr = L"���������ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	unsigned char len = 0;
	unsigned char firstKey[16] = {0};
	ret = keyboard.GetInputPass(readerHandle, 15, &len, 1, 0, firstKey);
	if (ret != 0)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		keyboard.Keyboard_Close(readerHandle);
		return outStr.AllocSysString();
	}
	keyboard.Keyboard_Close(readerHandle);

	//��ȡ�ڶ�����������
	readerHandle = keyboard.Keyboard_Open("USB1");
	if (readerHandle <= 0)
	{
		outStr = L"���������ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	len = 0;
	unsigned char secondKey[16] = {0};
	ret = keyboard.GetInputPass(readerHandle, 15, &len, 1, 0, secondKey);
	if (ret != 0)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		keyboard.Keyboard_Close(readerHandle);
		return outStr.AllocSysString();
	}
	keyboard.Keyboard_Close(readerHandle);

	if (strcmp((const char*)firstKey, (const char*)secondKey) != 0)
	{
		reader->CloseReader(devNo);
		devNo = NULL;
		outStr = L"������������벻һ��";
		return outStr.AllocSysString();
	}

	//У��PIN
	cmd.Format(L"00200000%02d%s", len/2, firstKey);
	memset(respData, 0, sizeof(respData));	
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr.Format(L"У��PINʧ��%x", ret);
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iChangePIN(LONG iType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	devNo = NULL;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}

	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//��Ƭ��λ 
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 0, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"iChangePIN��λ��Ƭʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//ѡ���籣����
	CString cmd("");
	cmd = CString("00A404000F7378312E73682EC9E7BBE1B1A3D5CF");	
	char respData[1024] = {0};	
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"iChangePINѡ���籣����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//��ȡ������
	int oldHandle = keyboard.Keyboard_Open("USB1");
	if (oldHandle <= 0)
	{
		outStr = L"���������ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	unsigned char oldLen = 0;
	unsigned char oldKey[16] = {0};
	ret = keyboard.GetInputPass(oldHandle, 15, &oldLen, 1, 0, oldKey);
	if (ret != 0)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		keyboard.Keyboard_Close(oldHandle);
		return outStr.AllocSysString();
	}
	keyboard.Keyboard_Close(oldHandle);

	//��ȡ��һ����������
	int readerHandle = keyboard.Keyboard_Open("USB1");
	if (readerHandle <= 0)
	{
		outStr = L"���������ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	unsigned char len = 0;
	unsigned char firstKey[16] = {0};
	ret = keyboard.GetInputPass(readerHandle, 15, &len, 1, 0, firstKey);
	if (ret != 0)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		keyboard.Keyboard_Close(readerHandle);
		return outStr.AllocSysString();
	}
	keyboard.Keyboard_Close(readerHandle);

	//��ȡ�ڶ�����������
	readerHandle = keyboard.Keyboard_Open("USB1");
	if (readerHandle <= 0)
	{
		outStr = L"���������ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	len = 0;
	unsigned char secondKey[16] = {0};
	ret = keyboard.GetInputPass(readerHandle, 15, &len, 1, 0, secondKey);
	if (ret != 0)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		keyboard.Keyboard_Close(readerHandle);
		return outStr.AllocSysString();
	}
	keyboard.Keyboard_Close(readerHandle);

	if (strcmp((const char*)firstKey, (const char*)secondKey) != 0)
	{
		reader->CloseReader(devNo);
		devNo = NULL;
		outStr = L"������������벻һ��";
		return outStr.AllocSysString();
	}

	//�޸�PIN
	cmd.Format(L"805E0100%02d%sFF%s", len/2 + 1 + oldLen/2, oldKey, firstKey);
	memset(respData, 0, sizeof(respData));	
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr.Format(L"У��PINʧ��%x", ret);
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReloadPIN(LONG iType, LPCTSTR pCardInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	devNo = NULL;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}
	
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//�����Ƿ���PSAM��
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 1, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"iReloadPIN��ⲻ��PSAM��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();		
	}
	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iUnblockPIN(LONG iType, LPCTSTR pCardInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	devNo = NULL;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}

	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//�����Ƿ���PSAM��
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 1, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"iUnblockPIN��ⲻ��PSAM��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();	
	}
	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iDoDebit(LONG iType, LPCTSTR pCardInfo, LPCTSTR pPayInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	devNo = NULL;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}

	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//�����Ƿ���PSAM��
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 1, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"iDoDebit��ⲻ��PSAM��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();	
	}
	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReadDebitRecord(LONG iType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	devNo = NULL;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 0, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"iReadDebitRecord��Ƭ��λʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();	
	}
	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReadCardBas_HSM_Step1(LONG iType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	devNo = NULL;
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}

	//��Ƭ��λ  ��ȡatr
	char respData[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 0, respData, &atrLen);
	if (ret != 0)
	{
		outStr = L"��Ƭ��λʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	char infoAtr[1024] = {0};
	reader->hexToAsc(respData, atrLen, infoAtr);

	//ѡ���籣����
	CString cmd("");
	cmd = CString("00A404000F7378312E73682EC9E7BBE1B1A3D5CF");	

	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ���籣����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//���ݿ�ʶ������ȷ���㷨����
	//��ȡʶ����
	cmd = CString("00A4000002EF05");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ��EF05Ŀ¼ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	cmd = CString("00B2010412");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡʶ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//����Ӧ������ȷ���㷨����
	CString buf = A2T(respData);
	buf = buf.Mid(4);
	buf.MakeUpper();
	CString algoCode(L"");
	int index = buf.Find(L"9F0C86");
	if (index != -1)
	{
		algoCode = buf.Mid(index + 6, 2);
		if (algoCode == L"01")
		{
			algoCode = L"DES";
		}else if (algoCode == L"02")
		{
			algoCode = L"SSF33";
		}else if (algoCode == L"03")
		{
			algoCode = L"SM4";
		}
	}else{
		buf = A2T(respData);
		buf = buf.Mid(4);
		buf.MakeUpper();
		algoCode = buf.Left(2);
		if (algoCode == L"11")
		{
			algoCode = L"SSF33";
		}else{
			algoCode = L"DES";
		}
	}

	CString tempVal = A2T(respData);
	CString rspVal = tempVal.Mid(4);
	tempVal = rspVal.Left(6);
	CString atr = A2T(infoAtr);
	atr = atr.Mid(8);

	char pOutInfo[1024] = {0};
	memset(pOutInfo, 0, sizeof(pOutInfo));
	sprintf(pOutInfo, "%s|%s|%s|%s", T2A(tempVal), T2A(atr), T2A(algoCode), T2A(rspVal));

	//��ȡ��������������ڲ���֤
	cmd = CString("0084000008");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�ڲ���֤�����ʧ��1";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	sprintf(pOutInfo, "%s|%s", pOutInfo, respData);

	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�ڲ���֤�����ʧ��2";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	sprintf(pOutInfo, "%s|%s", pOutInfo, respData);

	//��ȡ���淶�汾
	cmd = CString("00B2030006");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ���淶�汾ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	buf = A2T(respData);
	char buffer[24] = {0};
	reader->ascToHex(T2A(buf.Mid(4)), strlen(respData) - 4, buffer);
	buf = A2T(buffer);
	buf.MakeUpper();
	if (buf.Find(L"3.0") != -1)
	{
		//��ȡ��������������ⲿ��֤
		cmd = CString("0084000008");
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0)
		{
			outStr = L"��ȡ�ⲿ��֤�����ʧ��";
			WriteLogStr(outStr);
			ret = reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
		sprintf(pOutInfo, "%s|%s", pOutInfo, respData);

		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"��ȡ�ⲿ��֤�����ʧ��";
			WriteLogStr(outStr);			
			ret = reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
		sprintf(pOutInfo, "%s|%s||", pOutInfo, respData);
	}else{
		sprintf(pOutInfo, "%s||||", pOutInfo);
	}

	strResult = A2T(pOutInfo);
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReadCardBas_HSM_Step2(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	CString cmd("");	
	char respData[1024] = {0};

	//�ڲ���֤	
	CStringArray arr1;
	arr1.RemoveAll();
	CString key(pKey);
	GetString(key, arr1, '|');
	if (arr1[0].GetLength() != 32)
	{
		outStr = L"���ܻ��������ݳ��ȴ���";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	cmd = L"0088000010", arr1[0];
	int ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"�ڲ���֤ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	if (arr1[1].GetLength() == 32)
	{
		cmd = L"0082000010" + arr1[1];
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"�ⲿ��֤ʧ��";
			WriteLogStr(outStr);
			reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
	}

	//ѡ��EFO5
	cmd = CString("00A40002EF05");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ��EF05Ŀ¼ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//��ȡʶ����
	cmd = CString("00B2010412");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡʶ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	CStringArray arr;
	arr.RemoveAll();
	CString tempVal =  A2T(respData);
	arr[3] = tempVal;
	tempVal = tempVal.Left(6);
	arr[0] = tempVal;

	//��ȡ����
	cmd = CString("00B207041B");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	tempVal = A2T(respData);
	arr[2] = tempVal;

	//��ȡ�淶�汾
	cmd = CString("00B2030406");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�淶�汾ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	tempVal = A2T(respData);
	arr[6] = tempVal;

	//��ȡ��������
	cmd = CString("00B2050406");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ��������ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	tempVal = A2T(respData);
	arr[7] = tempVal;

	//��ȡ����Ч��
	cmd = CString("00B2060412");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ����Ч��ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	tempVal = A2T(respData);
	arr[8] = tempVal;

	//��ȡ��ᱣ�Ϻ���
	cmd = CString("00A40002EF06");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ��EF06Ŀ¼ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	cmd = CString("00B2010414");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ��ᱣ�Ϻ���ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	tempVal = A2T(respData);
	arr[1] = tempVal;

	//��ȡ����	
	cmd = CString("00B2020420");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	tempVal = A2T(respData);
	arr[4] = tempVal;

	arr[9] = "000000";
	arr[10] = "MW";
	char pOutInfo[1024] = {0};
	sprintf(pOutInfo, "%S|%S|%S|%S|%S|%S|%S|%S|%S|%S|%S|", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9], arr[10]);

	//�ر��豸
	ret = reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


CStringArray turnOver;
BSTR CGYHMeterCtrl::iReadCard_HSM_Step1(LONG iType, LPCTSTR pCardInfo, LPCTSTR pFileAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	if (devNo)
	{
		reader->CloseReader(devNo);
		devNo = NULL;
	}

	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}

	//��Ƭ��λ
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 0, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"��Ƭ��λʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//ѡ���籣����
	CString cmd("");
	cmd = CString("00A404000F7378312E73682EC9E7BBE1B1A3D5CF");
	char respData[1024] = {0};
	char respLen = 0;
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ���籣����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	//����Ӧ������ȷ���㷨����
	CString buf = A2T(respData);
	buf = buf.Mid(4);
	buf.MakeUpper();
	CString algoCode("");
	int index = buf.Find(L"9F0C86");

	//���ݿ�ʶ������ȷ���㷨����
	cmd = CString("00A4000002EF05");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ��EF05Ŀ¼ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	CString headingCode;
	if (index == -1)
	{		
		cmd = CString("00B2010412");
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"��ȡʶ����ʧ��";
			WriteLogStr(outStr);
			ret = reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
		buf = A2T(respData);
		buf = buf.Mid(4);
		buf.MakeUpper();
		headingCode = buf;
		algoCode = buf.Left(2);
		if (algoCode == "11")
		{
			algoCode = "SSF33";
		}else{
			algoCode = "DES";
		}
	}else{
		algoCode = buf.Mid(index + 6, 2);
		if (algoCode == "01")
		{
			algoCode = "DES";
		}else if (algoCode == "02")
		{
			algoCode = "SSF33";
		}else if (algoCode == "03")
		{
			algoCode = "SM4";
		}
	}
	//��ȡ����
	cmd = CString("00B207040B");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	CString cardNo = A2T(respData);
	cardNo = cardNo.Mid(4);

	//��ȡ���pCardInfo��������Ϣ
	CStringArray arr;
	arr.RemoveAll();
	CString tempStr(pCardInfo);
	GetString(tempStr, arr, '|');
	if (cardNo != arr[1] || headingCode != arr[0])
	{
		outStr = L"������Ϣ�������������Ӧ";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//��ȡ���pFileAddr��Ҫ�������ļ����ļ��µ�������
	CString fileLine(pFileAddr);
	arr.RemoveAll();
	GetString(fileLine, arr, '$');
	int size = arr.GetSize();
	fileLine = arr[0];	
	arr.RemoveAll();
	GetString(fileLine, arr, '|');

	char pOutInfo[1024] = {0};
	if (arr[0] == "SSSEEF05" || arr[0] == "SSSEEF06" || arr[0] == "DF01EF16" || arr[0] == "DF01EF17" || arr[0] == "DF01EF18" || arr[0] == "DF01EF19" || arr[0] == "DF01EF1A")
	{
		//���ɶ�ȡ 
		outStr = L"���ɶ�ȡ";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}else if (arr[0] == "SSSEEF07" || arr[0] == "SSSEEF08" || arr[0] == "DF07EF05" || arr[0] == "DF07EF06" || arr[0] == "DF07EF07")
	{
		//��ԿУ��
		if (arr[0] == "SSSEEF07" || arr[0] == "SSSEEF08")
		{
			sprintf(pOutInfo, "%S|%S", algoCode, "004C0A");
		}else if (arr[0] == "DF07EF05")
		{
			sprintf(pOutInfo, "%S|%S", algoCode, "007A3D");
		}else if (arr[0] == "DF07EF06")
		{
			sprintf(pOutInfo, "%S|%S", algoCode, "00803F");
		}else if (arr[0] == "DF07EF07")
		{
			sprintf(pOutInfo, "%S|%S", algoCode, "0086B1");
		}
	}else if (arr[0] == "DF04EF06")
	{
		//PINУ�����ԿУ��

		//��ȡ��һ����������
		int readerHandle = keyboard.Keyboard_Open("USB1");
		unsigned char len = 0;
		unsigned char firstKey[16] = {0};
		keyboard.GetInputPass(readerHandle, 15, &len, 1, 0, firstKey);
		keyboard.Keyboard_Close(readerHandle);

		//��ȡ�ڶ�����������
		readerHandle = keyboard.Keyboard_Open("USB1");
		len = 0;
		unsigned char secondKey[16] = {0};
		keyboard.GetInputPass(readerHandle, 15, &len, 1, 0, secondKey);
		keyboard.Keyboard_Close(readerHandle);

		if (strcmp((const char*)firstKey, (const char*)secondKey) != 0)
		{
			reader->CloseReader(devNo);
			devNo = NULL;
			outStr = L"������������벻һ��";
			return outStr.AllocSysString();
		}
		//У��PIN
		CString rKey = A2T((char*)secondKey);
		cmd.Format(L"00200000%02d%s", rKey.GetLength(), rKey);
		//cmd = CString("00200000");

		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);		
		if (ret != 0x9000)
		{
			outStr = L"У��PINʧ��";
			WriteLogStr(outStr);
			ret = reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}		
	}else if (arr[0] == "DF04EF06")
	{
		//PINУ��
		outStr = L"PINУ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}else{
		//PINУ�����ԿУ��

		//����ԿУ��
		if (arr[0] == "DF01EF05" || arr[0] == "DF01EF06" || arr[0] == "DF01EF07" || arr[0] == "DF01EF08" || arr[0] == "DF01EF09" || arr[0] == "DF01EF0A" || arr[0] == "DF01EF15")
		{
			sprintf(pOutInfo, "%S|%S", algoCode, "004F2E");
		}else if (arr[0] == "DF02EF05" || arr[0] == "DF02EF06" || arr[0] == "DF02EF07" || arr[0] == "DF02EF09" || arr[0] == "DF02EF15" || arr[0] == "DF02EF16")
		{
			sprintf(pOutInfo, "%S|%S", algoCode, "006435");
		}else if (arr[0] == "DF03EF05")
		{
			sprintf(pOutInfo, "%S|%S", algoCode, "01962C");
		}else if (arr[0] == "DF04EF05" || arr[0] == "DF04EF15")
		{
			sprintf(pOutInfo, "%S|%S", algoCode, "01822D");
		}else{
			sprintf(pOutInfo, "%S|%S", algoCode, "01932B");
		}
	}

	//��ȡ��������������ⲿ��֤
	cmd = CString("0084000008");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	sprintf(pOutInfo, "%S|%S", pOutInfo, respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�ⲿ��֤�����ʧ��1";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�ⲿ��֤�����ʧ��2";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
	}
	sprintf(pOutInfo, "%S|%S|", pOutInfo, respData);
	strResult = A2T(pOutInfo);
	turnOver.RemoveAll();
	//turnOver = arr;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReadCard_HSM_Step2(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	//�ⲿ��֤
	CString lKey(pKey);
	if (lKey.GetLength() != 32)
	{
		outStr = L"���ܻ��������ݳ��ȴ���";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	CString cmd = L"0082000010" + lKey;
	char respData[1024];
	char respLen;
	int ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"�ⲿ��֤ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	CString strDF;
	CString strEF;	
	if (turnOver[0].Find(L"SSSE") == -1)
	{
		strDF = turnOver[0].Left(4);	
	}else{
		strDF = L"";
	}	
	strEF = turnOver[0].Mid(4);	

	cmd = CString("00A40000023F00");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);	
	if (ret != 0x9000)
	{
		outStr = L"ѡ���籣Ŀ¼ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	if (strDF.GetLength() != 0)
	{
		cmd = CString("00A4000002") + strDF;
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"ѡ��Ŀ¼ʧ��";
			WriteLogStr(outStr);
			ret = reader->CloseReader(devNo);
			devNo = NULL;
		}
	}

	cmd = CString("00A4000002") + strEF;
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ��Ŀ¼ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
	}

	int size = turnOver.GetSize();
	for (int i = 1; i < size; i++)
	{
		cmd.Format(L"00b2%s0000", turnOver[i]);
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"������ʧ��";
			WriteLogStr(outStr);
			ret = reader->CloseReader(devNo);
			devNo = NULL;
		}
	}
	ret = reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iWriteCard_HSM_Step1(LONG iType, LPCTSTR pCardInfo, LPCTSTR pFileAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	if (devNo)
	{
		reader->CloseReader(devNo);
		devNo = NULL;
	}

	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, 2, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}

	//��Ƭ��λ
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 0, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"��Ƭ��λʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//ѡ���籣����
	CString cmd("");
	cmd = CString("00A404000F7378312E73682EC9E7BBE1B1A3D5CF");
	char respData[1024] = {0};
	char respLen = 0;
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ���籣����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	//����Ӧ������ȷ���㷨����
	CString buf = A2T(respData);
	buf = buf.Mid(4);
	buf.MakeUpper();
	CString algoCode("");
	int index = buf.Find(L"9F0C86");

	//���ݿ�ʶ������ȷ���㷨����
	cmd = CString("00A4000002EF05");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ��EF05Ŀ¼ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	CString headingCode;
	if (index == -1)
	{		
		cmd = CString("00B2010412");
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"��ȡʶ����ʧ��";
			WriteLogStr(outStr);
			ret = reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
		buf = A2T(respData);
		buf = buf.Mid(4);
		buf.MakeUpper();
		headingCode = buf;
		algoCode = buf.Left(2);
		if (algoCode == "11")
		{
			algoCode = "SSF33";
		}else{
			algoCode = "DES";
		}
	}else{
		algoCode = buf.Mid(index + 6, 2);
		if (algoCode == "01")
		{
			algoCode = "DES";
		}else if (algoCode == "02")
		{
			algoCode = "SSF33";
		}else if (algoCode == "03")
		{
			algoCode = "SM4";
		}
	}
	//��ȡ����
	cmd = CString("00B207040B");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	CString cardNo = A2T(respData);
	cardNo = cardNo.Mid(4);

	//��ȡ���pCardInfo��������Ϣ
	CStringArray arr;
	arr.RemoveAll();
	CString tempStr(pCardInfo);
	GetString(tempStr, arr, '|');
	if (cardNo != arr[1] || headingCode != arr[0])
	{
		outStr = L"������Ϣ�������������Ӧ";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//��ȡ���pFileAddr��Ҫ�������ļ����ļ��µ�������
	CString fileLine(pFileAddr);
	arr.RemoveAll();
	GetString(fileLine, arr, '$');
	int size = arr.GetSize();
	fileLine = arr[0];	
	arr.RemoveAll();
	GetString(fileLine, arr, '|');

	char pOutInfo[1024] = {0};

	CString indexKey;
	if (arr[0] == "SSSEEF05" || arr[0] == "SSSEEF06" || arr[0] == "SSSEEF07")
	{
		indexKey = L"009412";
	}else if (arr[0] == "DF01EF05")
	{
		indexKey = L"009742";
	}
	else if (arr[0] == "DF01EF06")
	{
		indexKey = L"017925";
	}else if (arr[0] == "DF01EF07")
	{
		indexKey = L"009A43";
	}else if (arr[0] == "DF01EF08")
	{
		indexKey = L"017624";
	}else if (arr[0] == "DF01EF0A")
	{
		indexKey = L"009742";
	}else if (arr[0] == "DF01EF05")
	{
		indexKey = L"009742";
	}
	

	//��ȡ��������������ⲿ��֤
	cmd = CString("0084000008");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	sprintf(pOutInfo, "%S|%S", pOutInfo, respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�ⲿ��֤�����ʧ��1";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�ⲿ��֤�����ʧ��2";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
	}
	sprintf(pOutInfo, "%S|%S|", pOutInfo, respData);
	strResult = A2T(pOutInfo);
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iWriteCard_HSM_Step2(LPCTSTR pKey, LPCTSTR pWriteData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	//�ⲿ��֤
	CString lKey(pKey);
	CString cmd = L"0082000010" + lKey;
	char respData[1024];	
	int ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"�ⲿ��֤ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	CStringArray arr;
	CString fileLine(pWriteData);
	arr.RemoveAll();
	GetString(fileLine, arr, '$');
	int size = arr.GetSize();
	fileLine = arr[1];
	arr.RemoveAll();
	GetString(fileLine, arr, '|');	
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReloadPIN_HSM_Step1(LONG iType, LPCTSTR pCardInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	devNo = NULL;
	int cardType = 1;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, cardType, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//��Ƭ��λ
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 0, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"��Ƭ��λʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//ѡ���籣����
	CString cmd("");
	cmd = CString("00A404000F7378312E73682EC9E7BBE1B1A3D5CF");
	char respData[1024] = {0};
	char respLen = 0;
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ���籣����ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	//����Ӧ������ȷ���㷨����
	CString buf = A2T(respData);
	buf.MakeUpper();
	CString algoCode("");
	int index = buf.Find(L"9F0C86");
	CString headingCode;
	if (index == -1)
	{
		//���ݿ�ʶ������ȷ���㷨����
		cmd = CString("00A4000002EF05");
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"ѡ��EF05Ŀ¼ʧ��";
			WriteLogStr(outStr);
			reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
		cmd = CString("00B2010412");
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"��ȡʶ����ʧ��";
			WriteLogStr(outStr);
			reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
		buf = A2T(respData);
		buf.MakeUpper();
		headingCode = buf;
		algoCode = buf.Left(2);
		if (algoCode == "11")
		{
			algoCode = "SSF33";
		}else{
			algoCode = "DES";
		}
	}else{
		algoCode = buf.Mid(index + 6, 2);
		if (algoCode == "01")
		{
			algoCode = "DES";
		}else if (algoCode == "02")
		{
			algoCode = "SSF33";
		}else if (algoCode == "03")
		{
			algoCode = "SM4";
		}
	}
	//��ȡ����
	cmd = CString("00B207040B");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	CString cardNo = A2T(respData);

	//��ȡ���pCardInfo��������Ϣ
	CStringArray arr;
	arr.RemoveAll();
	CString tempStr(pCardInfo);
	GetString(tempStr, arr, '|');
	if (cardNo != arr[1] || headingCode != arr[0])
	{
		outStr = L"������Ϣ���������ݲ���Ӧ";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	char pOutInfo[1024] = {0};
	sprintf(pOutInfo, "%S|%S|", algoCode, "009010");

	//��ȡ��������������ⲿ��֤
	cmd = CString("0084000008");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);	
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�����ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	sprintf(pOutInfo, "%S|%S|", pOutInfo, respData);

	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�����ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	sprintf(pOutInfo, "%S|%S|", pOutInfo, respData);
	strResult = A2T(pOutInfo);
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReloadPIN_HSM_Step2(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	CString lKey(pKey);
	if (lKey.GetLength() != 32)
	{
		outStr = L"���ܻ��������ݳ��ȴ���";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	//�ⲿ��֤
	CString cmd = L"0082000010" + lKey;
	char respData[1024];	
	int ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"�ⲿ��֤ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//��ȡ��һ����������
	int readerHandle = keyboard.Keyboard_Open("USB1");
	if (readerHandle <= 0)
	{
		outStr = L"���������ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	unsigned char len = 0;
	unsigned char firstKey[16] = {0};
	ret = keyboard.GetInputPass(readerHandle, 15, &len, 1, 0, firstKey);
	if (ret != 0)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		keyboard.Keyboard_Close(readerHandle);
		return outStr.AllocSysString();
	}
	keyboard.Keyboard_Close(readerHandle);

	//��ȡ�ڶ�����������
	readerHandle = keyboard.Keyboard_Open("USB1");
	if (readerHandle <= 0)
	{
		outStr = L"���������ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	len = 0;
	unsigned char secondKey[16] = {0};
	ret = keyboard.GetInputPass(readerHandle, 15, &len, 1, 0, secondKey);
	if (ret != 0)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		ret = reader->CloseReader(devNo);
		devNo = NULL;
		keyboard.Keyboard_Close(readerHandle);
		return outStr.AllocSysString();
	}
	keyboard.Keyboard_Close(readerHandle);

	if (strcmp((const char*)firstKey, (const char*)secondKey) != 0)
	{
		outStr = L"�������벻һ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	//��ȡ��������
	cmd = CString("0084000008");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret!= 0x9000)
	{
		outStr = L"��ȡ��ȫ���ļ����������ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	char pOutInfo[1024] = {0};
	sprintf(pOutInfo, "%S|%S|%S|%S|", flag, "009010", respData, "84D4", firstKey);
	strResult = A2T(pOutInfo);
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReloadPIN_HSM_Step3(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	CString cmd(pKey);
	int len = cmd.GetLength();
	if (len != 34 && len != 50)
	{
		outStr = L"���ܻ��������ݳ��ȴ���";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	
	char respData[1024];	
	int ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"����PINʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iUnblockPIN_HSM_Step1(LONG iType, LPCTSTR pCardInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	devNo = NULL;
	int cardType = 1;
	if (iType == 2)
	{
		outStr = L"Ѱ��ʧ��";		
		WriteLogStr(outStr);		
		return outStr.AllocSysString();
	}
	//�򿪶�д��
	int ret = reader->OpenReader("USB1", &devNo, cardType, 0);
	if (ret != 0)
	{
		outStr = L"�򿪶�д��ʧ��";
		WriteLogStr(outStr);
		return outStr.AllocSysString();
	}

	//��Ƭ��λ
	char infoATR[1024] = {0};
	char atrLen = 0;
	ret = reader->ResetCard(devNo, 0, infoATR, &atrLen);
	if (ret != 0)
	{
		outStr = L"��Ƭ��λʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//ѡ���籣����
	CString cmd = L"00A404000F7378312E73682EC9E7BBE1B1A3D5CF";
	char respData[1024] = {0};
	char respLen = 0;
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"ѡ���籣����ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	//����Ӧ������ȷ���㷨����
	CString buf = A2T(respData);
	buf.MakeUpper();
	CString algoCode("");
	int index = buf.Find(L"9F0C86");
	CString headingCode;
	if (index == -1)
	{
		//���ݿ�ʶ������ȷ���㷨����
		cmd = CString("00A4000002EF05");
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"ѡ��EF05ʧ��";
			WriteLogStr(outStr);
			reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
		cmd = CString("00B2010412");
		ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
		if (ret != 0x9000)
		{
			outStr = L"��ȡʶ����ʧ��";
			WriteLogStr(outStr);
			reader->CloseReader(devNo);
			devNo = NULL;
			return outStr.AllocSysString();
		}
		buf = A2T(respData);
		buf.MakeUpper();
		headingCode = buf;
		algoCode = buf.Left(2);
		if (algoCode == "11")
		{
			algoCode = "SSF33";
		}else{
			algoCode = "DES";
		}
	}else{
		algoCode = buf.Mid(index + 6, 2);
		if (algoCode == "01")
		{
			algoCode = "DES";
		}else if (algoCode == "02")
		{
			algoCode = "SSF33";
		}else if (algoCode == "03")
		{
			algoCode = "SM4";
		}
	}
	//��ȡ����
	cmd = CString("00B207040B");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ����ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	CString cardNo = A2T(respData);

	//��ȡ���pCardInfo��������Ϣ
	CStringArray arr;
	arr.RemoveAll();
	CString tempStr(pCardInfo);
	GetString(tempStr, arr, '|');
	if (cardNo != arr[1] || headingCode != arr[0])
	{
		outStr = L"������Ϣ�������������Ӧ";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	char pOutInfo[1024] = {0};
	sprintf(pOutInfo, "%S|%S|", algoCode, "009010");

	//��ȡ��������������ⲿ��֤
	cmd = CString("0084000008");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);	
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�����ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	sprintf(pOutInfo, "%S|%S|", pOutInfo, respData);

	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"��ȡ�����ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	sprintf(pOutInfo, "%S|%S|", pOutInfo, respData);
	strResult = A2T(pOutInfo);
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iUnblockPIN_HSM_Step2(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	//�ⲿ��֤
	CString lKey(pKey);
	if (lKey.GetLength() != 32)
	{
		outStr = L"���ܻ��������ݳ��ȴ���";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	CString cmd = L"0082000010" + lKey;
	char respData[1024];	
	int ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"�ⲿ��֤ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}

	//��ȡ��������
	cmd = CString("0084000008");
	ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret!= 0x9000)
	{
		outStr = L"��ȡ��ȫ���ļ����������ʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}	
	char pOutInfo[1024] = {0};
	sprintf(pOutInfo, "%S|%S|%S|%S|", flag, "009010", respData, "8424", "");
	strResult = A2T(pOutInfo);
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iUnblockPIN_HSM_Step3(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	USES_CONVERSION;
	CString cmd(pKey);
	int len = cmd.GetLength();
	if (len != 18)
	{
		outStr = L"���ܻ��������ݳ��ȴ���";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	
	char respData[1024] = {0};	
	int ret = reader->ApduCard(devNo, 0, T2A(cmd), cmd.GetLength(), respData);
	if (ret != 0x9000)
	{
		outStr = L"����PINʧ��";
		WriteLogStr(outStr);
		reader->CloseReader(devNo);
		devNo = NULL;
		return outStr.AllocSysString();
	}
	reader->CloseReader(devNo);
	devNo = NULL;
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iDoDebit_HSM_Step1(LONG iType, LPCTSTR pCardInfo, LPCTSTR pPayInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	strResult = L"";
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iDoDebit_HSM_Step2(LPCTSTR pKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	strResult = L"";
	return strResult.AllocSysString();
}




BSTR CGYHMeterCtrl::iReadICCardNum(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	strResult = L"";
	return strResult.AllocSysString();
}


BSTR CGYHMeterCtrl::iReadIdentityCard(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	BOOL flag = FALSE;
	ULONG_PTR userdata = 0;	
	flag = ZZOpenIdCardEx(FALSE, (IdCardCallback)fIdCard, userdata);
	if (!flag)
	{		
		strResult = L"";
		return strResult.AllocSysString();
	}
	flag = ZZReadIdCard();
	CString xm = ZZGetIdCardResult(1);//����
	CString xb = ZZGetIdCardResult(2);//�Ա�
	CString mz = ZZGetIdCardResult(3);//����
	CString year = ZZGetIdCardResult(4);//������
	CString month = ZZGetIdCardResult(5);//������
	CString day = ZZGetIdCardResult(6);//������
	CString zh = ZZGetIdCardResult(7);//סַ
	CString sfz = ZZGetIdCardResult(8);//���֤
	CString fzjg = ZZGetIdCardResult(9);//��֤����
	CString yxqksn = ZZGetIdCardResult(10);//��Ч����ʼ��
	CString yxqksy = ZZGetIdCardResult(11);//��Ч����ʼ��
	CString yxqksr = ZZGetIdCardResult(12);//��Ч����ʼ��
	CString yxqjsn = ZZGetIdCardResult(13);//��Ч�ڽ�����
	CString yxqjsy = ZZGetIdCardResult(14);//��Ч�ڽ�����
	CString yxqjsr = ZZGetIdCardResult(15);//��Ч�ڽ�����
	CString tmp = L"1.jpg";
	flag = ZZGetIdCardImage(tmp, 2);
	if (!flag)
	{		
		strResult = L"";
		ZZCloseIdCard();
		return strResult.AllocSysString();
	}
	BSTR baseStr = ZZGetBase64(L"1.jpg");
	CString lJpg(baseStr);
	strResult.Format(_T("%s|%s|%s|%s%s%s|%s|%s|%s%s%s|%s%s%s|%s|"), xm, xb, mz, year, month, day, sfz, fzjg, yxqksn, yxqksy, yxqksr, yxqjsn, yxqjsy, yxqjsr, lJpg);
	ZZCloseIdCard();
	ZZReleaseString(baseStr);
	return strResult.AllocSysString();
}
