// GYHMeter.cpp : CGYHMeterApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "GYHMeter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGYHMeterApp theApp;

const GUID CDECL _tlid = { 0x109392B, 0x5F40, 0x4D49, { 0xB7, 0x67, 0xA4, 0xFC, 0xC9, 0xE3, 0xB, 0x7C } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGYHMeterApp::InitInstance - DLL 初始化

BOOL CGYHMeterApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CGYHMeterApp::ExitInstance - DLL 终止

int CGYHMeterApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
