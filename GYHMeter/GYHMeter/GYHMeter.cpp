// GYHMeter.cpp : CGYHMeterApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "GYHMeter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGYHMeterApp theApp;

const GUID CDECL _tlid = { 0x109392B, 0x5F40, 0x4D49, { 0xB7, 0x67, 0xA4, 0xFC, 0xC9, 0xE3, 0xB, 0x7C } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGYHMeterApp::InitInstance - DLL ��ʼ��

BOOL CGYHMeterApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CGYHMeterApp::ExitInstance - DLL ��ֹ

int CGYHMeterApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
