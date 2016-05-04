#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

#pragma once
#include "../../YMusic.h"
//<By dnf.li 2013-9-11> ����ҵ����http���󶼴������.
class CServerManager : public Singleton<CServerManager>
{
public:
	CServerManager();
	~CServerManager();
public:
	int Login(CString& userName, CString& password);
	int Login(CString& sToken);
	int Share(int nObjId, CString& sCommentMsg);
public:
	int DownLoad(LPCTSTR lpszUrl,LPCTSTR lpszFile);
};


#endif