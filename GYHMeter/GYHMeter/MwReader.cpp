#include "StdAfx.h"
#include "MwReader.h"

MwReader::MwReader(void)
{
	hmodle = NULL;
	LoadDll();	
}

MwReader::~MwReader(void)
{
	if(hmodle)
		FreeLibrary(hmodle);
	hmodle = NULL;
	mw_dev_openReader = NULL;
	mw_cpu_reset = NULL;
	mw_cpu_apdu = NULL;
	mw_cpu_powerDown = NULL;
	mw_dev_closeReader = NULL;
}

BOOL MwReader::LoadDll()
{
	HINSTANCE hOcx = ::GetModuleHandle(L"GYHMeter.ocx"); 
	CString strPath; 
	::GetModuleFileNameW(hOcx, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int index = strPath.ReverseFind('\\');
	strPath = strPath.Mid(0, index + 1);
	SetCurrentDirectory(strPath);

	if ((hmodle = GetModuleHandle(_T("mwCardReader.dll"))) == NULL)
	{
		hmodle = LoadLibrary(_T("mwCardReader.dll"));
	}

	if (hmodle == NULL || hmodle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	mw_dev_openReader = (pmw_dev_openReader) GetProcAddress(hmodle, "mw_dev_openReader");
	mw_cpu_reset = (pmw_cpu_reset) GetProcAddress(hmodle, "mw_cpu_reset");
	mw_cpu_apdu	= (pmw_cpu_apdu) GetProcAddress(hmodle, "mw_cpu_apdu");
	mw_cpu_powerDown = (pmw_cpu_powerDown) GetProcAddress(hmodle, "mw_cpu_powerDown");
	mw_dev_closeReader = (pmw_dev_closeReader) GetProcAddress(hmodle, "mw_dev_closeReader");
	mw_ext_hexToAsc = (pmw_ext_hexToAsc)GetProcAddress(hmodle, "mw_ext_hexToAsc");
	mw_ext_ascToHex = (pmw_ext_ascToHex)GetProcAddress(hmodle, "mw_ext_ascToHex");

	if(mw_dev_openReader!= 0 && mw_cpu_reset!=0 && mw_cpu_apdu!=0 &&  mw_cpu_powerDown!=0 &&  mw_dev_closeReader !=0 && mw_ext_hexToAsc != 0 && mw_ext_ascToHex != 0)
	{
		return true;
	}
	else
		return false;
}

int MwReader::OpenReader(char* name, HANDLE* devNo, int param1, int param2)
{
	int ret = mw_dev_openReader(name, devNo, param1, param2);
	if (ret != 0)
	{
		return 1;
	}
	return 0;
}

int MwReader::CloseReader(HANDLE devNo)
{
	int ret = mw_dev_closeReader(devNo);
	if (ret != 0)
	{
		return 1;
	}
	return 0;
}

int MwReader::ResetCard(HANDLE devNo, int iCardSeat, char* infoATR, char* atrLen)
{
	int ret = mw_cpu_reset(devNo, iCardSeat, infoATR, atrLen);
	if (ret != 0)
	{
		return 1;
	}
	return 0;
}

int MwReader::ApduCard(HANDLE devNo, int iCardSeat, char* apduData, int apduLen, char* respData)
{
	if(apduLen == 0)
		apduLen = strlen(apduData);

	char outBuff[256] = {0}; 
	memcpy(outBuff, apduData, apduLen);

	char hexApdu[1024 * 4];
	memset(hexApdu, 0, 1024 * 4);

	ascToHex(apduData, apduLen, hexApdu);

	char hexrespData[1024 * 4] = { 0 };	
	INT32 respLen = 0;

	int iRet = mw_cpu_apdu(devNo, iCardSeat, hexApdu, apduLen/2, hexrespData, &respLen);
	if (respLen <= 1 || iRet!=0)
	{
		return 0;
	}
	else if (hexrespData[respLen - 2] == 0x61)
	{
		hexApdu[0] = 0x00;
		hexApdu[1] = 0xC0;
		hexApdu[2] = 0x00;
		hexApdu[3] = 0x00;
		hexApdu[4] = hexrespData[respLen - 1];
		respLen = sizeof(hexrespData);

		respLen = 0; 
		int iRet = mw_cpu_apdu(devNo, iCardSeat, hexApdu, 5, hexrespData, &respLen);
		if (respLen <= 1 || iRet!=0)
		{
			return 0;
		}
		else
		{
			memset(respData, 0, respLen - 2);
			char str[16];
			for (int i = 0; i < respLen-2; i++)
			{
				memset(str, 0, 4);
				BYTE data = hexrespData[i];
				sprintf(str, "%02x", data);
				strcat(respData, str);
			}
		}
	}
	else
	{
		memset(respData, 0, respLen - 2);
		char str[16];
		for (int i = 0; i < respLen - 2; i++)
		{
			memset(str, 0, 4);
			BYTE data = hexrespData[i];
			sprintf(str, "%02x", data);
			strcat(respData, str);
		}
	}
	DWORD res = 0;
	if (respLen<1024 || respLen>2)
	{
		hexApdu[0] = hexrespData[respLen - 1];
		hexApdu[1] = hexrespData[respLen - 2];
		memcpy((DWORD*)&res, &hexApdu[0], 2);
	}

	return res;
}

int MwReader::PowerDownCard(HANDLE devNo, int iCardSeat)
{
	int ret = mw_cpu_powerDown(devNo, iCardSeat);
	if (ret != 0)
	{
		return 1;
	}
	return 0;
}

int MwReader::ascToHex(const char *srcAsc, int srcLen, char* dstHex)
{
	int ret = mw_ext_ascToHex(srcAsc, srcLen, dstHex);
	if (ret != 0)
	{
		return 1;
	}
	return 0;
}

int MwReader::hexToAsc(const char *srcHex, int hexLen, char* dstAsc)
{
	int ret = mw_ext_hexToAsc(srcHex, hexLen, dstAsc);
	if (ret != 0)
	{
		return 1;
	}
	return 0;
}