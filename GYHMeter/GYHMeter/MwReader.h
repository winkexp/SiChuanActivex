#pragma once
#include "gyreader.h"

typedef int(__stdcall *pmw_dev_openReader)(char* name, HANDLE *devNo, int param1, int param2);
typedef int(__stdcall *pmw_cpu_reset)(HANDLE devNo, int ivCardSeat, char *infoATR, char *atrLen);
typedef int(__stdcall *pmw_cpu_apdu)(HANDLE devNo, int ivCardSeat, char *apduData, int apduLen, char *respData, int *respLen);//上电 冷 返回数据长度
typedef int(__stdcall *pmw_cpu_powerDown)(HANDLE devNo, int ivCardSeat);
typedef int(__stdcall *pmw_dev_closeReader)(HANDLE devNo);
typedef int(__stdcall *pmw_ext_ascToHex)(const char *srcAsc, int srcLen, char* dstHex);
typedef int(__stdcall *pmw_ext_hexToAsc)(const char *srcHex, int hexLen, char* dstAsc);


class MwReader :
	public GyReader
{
public:
	MwReader(void);
	~MwReader(void);
	 HMODULE  hmodle;
	HANDLE  m_hReader;
	pmw_dev_openReader		mw_dev_openReader ;
	pmw_cpu_reset			mw_cpu_reset ;
	pmw_cpu_apdu			mw_cpu_apdu ;
	pmw_cpu_powerDown		mw_cpu_powerDown;
	pmw_dev_closeReader		mw_dev_closeReader;
	pmw_ext_ascToHex		mw_ext_ascToHex;
	pmw_ext_hexToAsc		mw_ext_hexToAsc;

	BOOL LoadDll();
	int OpenReader(char* name, HANDLE* devNo, int param1, int param2);
	int CloseReader(HANDLE devNo);
	int ResetCard(HANDLE devNo, int iCardSeat, char* infoATR, char* atrLen);
	int PowerDownCard(HANDLE devNo, int iCardSeat);
	int ApduCard(HANDLE devNo, int iCardSeat, char* apduData, int apduLen, char* respData);
	int ascToHex(const char *srcAsc, int srcLen, char* dstHex);
	int hexToAsc(const char *srcHex, int hexLen, char* dstAsc);
};
