// QQ.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "QQ.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);


	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;
	Console::Write(_T("���%.2f\n"), 111.011f);
	VSOutput::Write(_T("���%.2f\n"), 100.0403f);

	theApp = new CMainWindow();
	if (theApp == NULL) return 0;
	theApp->Create(NULL, _T("QQ2013"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	theApp->CenterWindow();
	theApp->ShowWindow(true);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}

