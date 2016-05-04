#include "stdafx.h"

#include "DatabaseManager.h"
#include "../YApp.h"

using namespace em_utility;

	const TCHAR * CDatabaseManager::USER_DB  = _T("user_%s.sl");
	const TCHAR * CDatabaseManager::DEFAULT_DB = _T("default.sl");
	const TCHAR * CDatabaseManager::GLOBEL_DB = _T("globel.sl"); 

	CDatabaseManager::CDatabaseManager()
	{

	}

	CDatabaseManager::~CDatabaseManager()
	{

	}

	void CDatabaseManager::SetDatabasePath(CString &sDatabasePath)
	{
		if(sDatabasePath.GetLength() == 0)
			return;
		m_sDatabasePath = sDatabasePath; 
		m_sDatabasePath.Replace(_T('\\'),_T('/'));
		
		if(_T('/') != m_sDatabasePath.Right(1))
		{
			m_sDatabasePath+=_T("/");	
		}
	}

	CString &CDatabaseManager::GetDatabasePath()
	{
		return m_sDatabasePath;
	}

	bool CDatabaseManager::SetCurrentUser(spLogonUserInfoT spUserInfo)
	{
		m_spUserInfo = spUserInfo;
		m_spUserDBase = spUserDBaseT(NULL);
		return true;
	}
	spGlobalDBaseT CDatabaseManager::GetGlobalDBase()
	{
		if(m_spGlobalDBase)
			return m_spGlobalDBase;
		sLog("��ʼ����ȫ�����ݿ�----���ݿ�");
		if(!m_spGlobalDBase && m_sDatabasePath.GetLength() > 0)
		{
			CString sDBFileName = theFilePathMgr->GetDatabasePath() + GLOBEL_DB;
			if(!mci::file_exist(sDBFileName))
			{
				
			}
			spGlobalDBaseT spGlobalDBase(new CGlobalDBase());
			if(spGlobalDBase && spGlobalDBase->OpenDB(sDBFileName))
			{
				m_spGlobalDBase = spGlobalDBase;
			}
		}
		sLog("��������ȫ�����ݿ�----���ݿ�");
		return m_spGlobalDBase;
	}
	spUserDBaseT CDatabaseManager::GetUserDBase()
	{
		if(m_spUserDBase)
			return m_spUserDBase;
		sLog("��ʼ�����û��б�----���ݿ�");
		if(!m_spUserDBase && m_spUserInfo && m_sDatabasePath.GetLength() > 0)
		{
			CString sDBFileName = theFilePathMgr->GetDatabasePath();
			CString sName;
			sName.Format(USER_DB,m_spUserInfo->sUserID);
			sDBFileName += sName;

			if(!mci::file_exist(sDBFileName))
			{

			}
			spUserDBaseT spUserDBase(new CUserDBase());
			if(spUserDBase && spUserDBase->OpenDB(sDBFileName))
			{
				m_spUserDBase = spUserDBase;
			}
		}
		sLog("���������û��б�----���ݿ�");
		return m_spUserDBase;
	}

	spUserDBaseT CDatabaseManager::GetDefaultUserDBase()
	{
		if(m_spDefaultUserDBase)
			return m_spDefaultUserDBase;
		sLog("��ʼ����Ĭ���б�----���ݿ�");
		if(!m_spDefaultUserDBase && m_sDatabasePath.GetLength() > 0)
		{
			CString sDBFileName = theFilePathMgr->GetDatabasePath() + DEFAULT_DB;

			if(!mci::file_exist(sDBFileName))
			{

			}
			spUserDBaseT spUserDBase(new CUserDBase());
			if(spUserDBase && spUserDBase->OpenDB(sDBFileName))
			{
				m_spDefaultUserDBase = spUserDBase;
			}
		}
		sLog("��������Ĭ���б�----���ݿ�");
		return m_spDefaultUserDBase;
	}
	spUserDBaseT CDatabaseManager::GetUserDB()
	{
		if (m_spUserInfo)
		{
			return GetUserDBase();
		}
		return GetDefaultUserDBase();
	}