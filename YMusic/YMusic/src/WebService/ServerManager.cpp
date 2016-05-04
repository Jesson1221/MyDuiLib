#include "StdAfx.h"
#include "ServerManager.h"
#include "HttpManager.h"
#include "HttpThread.h"
#include "../YApp.h"
CServerManager::CServerManager(){}
CServerManager::~CServerManager(){}

//--------------------------------------------------------------
int CServerManager::Login(CString& userName, CString& password)
{
	std::string sUtf8UserName = em_utility::mci::unicode_2_utf8(userName);
	std::string sUtf8PassWord = em_utility::mci::unicode_2_utf8(password); 
	CString web_url = _T("http://www.douban.com/j/app/login?email=%s&password=%s&app_name=radio_desktop_win&version=100");
	CString sUrl; sUrl.Format(web_url,userName,password);
	std::string sUtf8Url = em_utility::mci::unicode_2_utf8(sUrl);

	CurlData* pdata = new CurlData();
	pdata->SetURL(sUtf8Url.c_str());
//	CHttpThread* thread = new CHttpThread;
//	CHttpThread *thread = new CHttpThread(pdata,NULL,WM_WEB_SERVICE);
//	thread->Start();
 	HttpManagerProto* Manager = new HttpManagerProto;
 	ASSERT(Manager);
 	Manager->CurlGlobalInit();
 	int ret = Manager->DoHttpGet(pdata);

	{
//		char* ret = pdata->buffer;
// 	if(ret[0] == '1')
// 	{
// 		return 1; //��¼�ɹ�.
// 	}
// 	if(ret[0] == '0')
// 	{
// 		return 0; //��¼��֤ʧ��.
// 	}
	}
	return -1; //��¼�����쳣.

}
//--------------------------------------------------------------
int CServerManager::Login(CString& sToken)
{
	return 0;
}
//--------------------------------------------------------------
int CServerManager::Share(int nObjId, CString& sCommentMsg)
{
	return 0;
}
//--------------------------------------------------------------
int CServerManager::DownLoad(LPCTSTR lpszUrl,LPCTSTR lpszFile)
{
	return 0;
}
