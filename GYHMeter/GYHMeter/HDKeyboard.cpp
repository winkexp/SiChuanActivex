#include "StdAfx.h"
#include "HDKeyboard.h"

HDKeyboard::HDKeyboard(void)
{
}

HDKeyboard::~HDKeyboard(void)
{
}

BOOL HDKeyboard::LoadDll()
{
	HINSTANCE hOcx = ::GetModuleHandle(L"GYHMeter.ocx"); 
	CString strPath; 
	::GetModuleFileNameW(hOcx, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int index = strPath.ReverseFind('\\');
	strPath = strPath.Mid(0, index + 1);
	SetCurrentDirectory(strPath);

	if ((hmodle = GetModuleHandle(_T("./lib/HD_KeyBoard.dll"))) == NULL)
	{
		hmodle = LoadLibrary(_T("./lib/HD_KeyBoard.dll"));
	}

	if (hmodle == NULL || hmodle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	ICC_Reader_Open = (pICC_Reader_Open) GetProcAddress(hmodle, "ICC_Reader_Open");
	ICC_GetInputPass = (pICC_GetInputPass) GetProcAddress(hmodle, "ICC_GetInputPass");
	ICC_Reader_Close	= (pICC_Reader_Close) GetProcAddress(hmodle, "ICC_Reader_Close");
	
	if(ICC_Reader_Open!= 0 && ICC_GetInputPass!=0 && ICC_Reader_Close)
	{
		return true;
	}
	else
		return false;
}

int HDKeyboard::Keyboard_Open(char* devName)
{
	return ICC_Reader_Open(devName);
}

int HDKeyboard::Keyboard_Close(long ReaderHandle)
{
	return ICC_Reader_Close(ReaderHandle);
}

int HDKeyboard::GetInputPass(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start, unsigned char stop,unsigned char *cpass)
{
	return ICC_GetInputPass(ReaderHandle, ctime, rlen, start, stop, cpass);
}