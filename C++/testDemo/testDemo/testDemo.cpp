// testDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "UsbDevInterface.h"

void __stdcall data(const char* p, const sPenInfo& penInfo, void* context)
{
    printf("%s\n", p);

    if(penInfo.nPens == 0)
        printf("pen leave\n");
    else if(penInfo.nPens == 16)
        printf("pen detected\n");
    else if(penInfo.nPens == 17)
        printf("write down\n");

    printf("X point %d\n", penInfo.nX);
    printf("Y point %d\n", penInfo.nY);
    printf("Pen pressure %d\n", penInfo.nPenP);
}

// ��̬����  �����һ��ӿ� _extern_openSpecUsbDevByPid��_extern_CloseUsbDev
int dynamicLoadingDllOne()
{
	HMODULE hm = LoadLibraryA("usbDevModule.dll");
	if (NULL == hm)
	{
		return 0;
	}
	bool ( *pFunPro)(char* pAarryPid[], unsigned int nAarrySize, void* pFunc) = (bool(*)(char* pAarryPid[], unsigned int nAarrySize, void* pFunc))GetProcAddress(hm, "_extern_openSpecUsbDevByPid");
	if (pFunPro == NULL)
	{
		FreeLibrary(hm);
		return 0;
	}
	char *arry[2] = {"7806", "7805"};
	bool bOpenRes = pFunPro(arry, 2, data);
	if (!bOpenRes)
	{
		FreeLibrary(hm);
		return 0;
	}
	// �ȴ�����
	system("pause");

	// ��ȡ�ر��豸�Ľӿ�
	bool (*pFunPro1)() = (bool (*)())GetProcAddress(hm, "_extern_CloseUsbDev");
	if (*pFunPro1 == NULL)
	{
		FreeLibrary(hm);
		return 0;
	}
	pFunPro1();
	FreeLibrary(hm);
	return 0;
}

// ��̬����  �õ�һ��ӿ� createObj��deleteObj
int dynamicLoadingDllTwo()
{
	HMODULE hm = LoadLibraryA("usbDevModule.dll");
	if (NULL == hm)
	{
		return 0;
	}
	CUsbDevInterface* ( *pFunPro)() = (CUsbDevInterface* (*)())GetProcAddress(hm, "createObj");
	if (pFunPro == NULL)
	{
		FreeLibrary(hm);
		return 0;
	}
	char *arry[2] = {"7806", "7805"};
	CUsbDevInterface* pDev = pFunPro();
	if (NULL == pDev)
	{
		FreeLibrary(hm);
		return 0;
	}

	bool bOpenDevRes = pDev->_openSpecUsbDevByPid(arry, 2, data);
	if (!bOpenDevRes)
	{
		printf("open device failure\r\n");
		system("pause");
		FreeLibrary(hm);
		return 0;
	}
	// �ȴ�����
	system("pause");
	pDev->closeUsbDev();
	// ��ȡ�ر��豸�Ľӿ�
	void (*pFunPro1)(void*) = (void (*)(void*))GetProcAddress(hm, "deleteObj");
	if (*pFunPro1 == NULL)
	{
		FreeLibrary(hm);
		return 0;
	}
	pFunPro1(pDev);
	FreeLibrary(hm);
	return 0;
}

// ��̬����
int staticLoadingDll()
{
	CUsbDevInterface* pusb = createObj();
	if (NULL == pusb)
		return 0;
	std::vector<std::string> vecPid;
	vecPid.push_back("7805");
	vecPid.push_back("7806");
	vecPid.push_back("7807");

	char *arry[2] = {"7806", "7805"};
	bool bOpen = pusb->_openSpecUsbDevByPid(arry, 2, data);
	if (!bOpen)
	{
		printf("open dev failed\n");
		system("pause");
		return 0;
	}

	system("pause");
	pusb->closeUsbDev();
	deleteObj(pusb);
	return 0;

	/*MSG msg = {0};
	while(msg.message != WM_QUIT) {
	if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}else {
	//TODO, do this
	//printf("123\n");
	}
	}*/
	//m_pUsbDev->_openSpecUsbDevByPid("7805", getUsbData);
	//system("pause");
	/*if (cobj._openSpecUsbDevByPid("7805", data))
	{
	printf("open dev  success\n");
	system("pause");
	cobj.close();
	}
	else
	{
	printf("open dev  fail\n");
	system("pause");
	}*/
}

int  _tmain(int argc, _TCHAR* argv[])
{
	// �ͻ�����ɸ����Լ�����ѡ����Ӧ�ļ��ط�ʽ
	// ��̬����dll
	return staticLoadingDll();

	// ��̬����dll
	return dynamicLoadingDllOne();

	// ��̬����dll
	return dynamicLoadingDllTwo();
}

