// Client.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Client.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	
	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;
	if (!AfxSocketInit())
	{
		MessageBox(NULL,_T("����Com����"),_T("Error"),MB_OK|MB_ICONERROR);
		return 0;
	}
	if(!AfxWinInit(::GetModuleHandle(NULL),NULL,::GetCommandLine(),0))
	{
		MessageBox(NULL,_T("�޷��ṩ���̴߳���"),_T("Error"),MB_OK|MB_ICONERROR);
		return 0;
	}
	theApp = new CMainWindow();
	if( theApp == NULL ) return 0;
	theApp->Create(NULL, _T("Ϻ��2013"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	theApp->CenterWindow();
	theApp->ShowWindow(true);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}