#pragma once

class GyReader
{
public:
	GyReader(void);
	virtual ~GyReader(void);
	virtual int OpenReader(char* name, HANDLE* devNo, int param1, int param2) = 0;
	virtual int CloseReader(HANDLE devNo) = 0;
	virtual int ResetCard(HANDLE devNo, int iCardSeat, char* infoATR, char* atrLen) = 0;
	virtual int PowerDownCard(HANDLE devNo, int iCardSeat) = 0;
	virtual int ApduCard(HANDLE devNo, int iCardSeat, char* apduData, int apduLen, char* respData) = 0;
	virtual int ascToHex(const char *srcAsc, int srcLen, char* dstHex) = 0;
	virtual int hexToAsc(const char *srcHex, int hexLen, char* dstAsc) = 0;
};
