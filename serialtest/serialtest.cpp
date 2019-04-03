#include <Windows.h>
#include <iostream>
#include<tchar.h>

using namespace std;
typedef HANDLE (*lpOpenCom)(TCHAR *);
typedef int (*lpSendData)(HANDLE , BYTE * ,DWORD );
typedef int (*lpRecData)(HANDLE, BYTE *);
typedef int (*lpClose)(HANDLE);
 
int _tmain(int argc, _TCHAR* argv[])
{
    lpOpenCom OpenCom;
    lpSendData SendData;
    lpRecData RecData;
    lpClose Close;
    HINSTANCE hDll;
	HANDLE hcom;

    hDll = LoadLibrary(L"..\\Debug\\NMC.dll");
	if (hDll == NULL)
	{
		printf("dll is not found");
		system("pause");
	}
	if (hDll != NULL)
	{
		OpenCom = (lpOpenCom)GetProcAddress(hDll, "OpenDriver");
		SendData = (lpSendData)GetProcAddress(hDll, "SendData");
		RecData = (lpRecData)GetProcAddress(hDll, "ReceiveData");
		Close = (lpClose)GetProcAddress(hDll, "ClosePort");

		/*	if (OpenCom == NULL)
			{
				cout << "the function addr is not found" << endl;
				system("pause");
			}
		*/

		if (OpenCom != NULL)
		{
			TCHAR *port = TEXT("COM3");
			hcom = OpenCom(port);
			if (hcom == NULL)
			{
				cout << "failed to open com" << endl;
				system("pause");
				return 0;
			}
		}

		if (SendData != NULL)
		{
			bool flag;
			BYTE data[] = { 0x01, 0x03, 0x00, 0x50, 0x00, 0x02, 0xC4, 0x1A };
			DWORD datalen = 8;
			flag = SendData(hcom, data, datalen);
			if (flag = false)
			{
				cout << "failed to send data " << endl;
				system("pause");
			}
			BYTE Rdata[12];
			bool Rflag;
			Rflag = RecData(hcom, Rdata);
			if (Rflag == false)
			{
				cout << "failed to receive data " << endl;
				system("pause");
			}
			cout << Rdata << endl;
		}
	}
			system("pause");

    return 0;
}