#pragma once

typedef int(__stdcall *pICC_Reader_Open)(char* devName);
typedef int(__stdcall *pICC_GetInputPass)(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start, unsigned char stop,unsigned char *cpass);
typedef int(__stdcall *pICC_Reader_Close)(long ReaderHandle);


class HDKeyboard
{
public:
	HDKeyboard(void);
	~HDKeyboard(void);

	pICC_Reader_Open ICC_Reader_Open;
	pICC_GetInputPass ICC_GetInputPass;
	pICC_Reader_Close ICC_Reader_Close;

	HMODULE hmodle;
	BOOL LoadDll();
	int Keyboard_Open(char* devName);
	int GetInputPass(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start, unsigned char stop,unsigned char *cpass);
	int Keyboard_Close(long ReaderHandle);
};
