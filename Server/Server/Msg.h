#ifndef CMSG1_H
#define CMSG1_H

#pragma once
namespace MSGTYPE
{
	static const TCHAR* SEP = _T("_");

	static const TCHAR* NULLMSG = _T("NULLMSG");
	static const TCHAR* NOMALMSG = _T("NOMALMSG");//һ��������Ϣ
	static const TCHAR* SYSTEMMSG = _T("SYSTEMMSG");//ϵͳ��Ϣ
	static const TCHAR* LOADMSG = _T("LOADMSG");//�����¼��Ϣ
	static const TCHAR* ERRORMSG = _T("ERRORMSG");//������Ϣ

	static const TCHAR* SERVERDOWN = _T("SERVERDOWN");//����˹ر�
	static const TCHAR* FAIL = _T("FAIL");//ʧ��
	static const TCHAR* SUCCESS = _T("SUCCESS");//�ɹ�
	static const TCHAR* NOID = _T("NOID");//δע��
	static const TCHAR* REGI = _T("REGI");//ע��
	static const TCHAR* OFLINE = _T("OFFLINE");//δ��¼
	static const TCHAR* LOAD = _T("LOAD");//��¼
	static const TCHAR* CLOSE = _T("CLOSE");//�ͻ����˳�
	static const TCHAR* CHANGE = _T("CHANGE");//�ͻ��˸���
	static const TCHAR* USERLIST = _T("USERLIST");//�û��б�
	static const TCHAR* CHAT = _T("CHAT");//������Ϣ
};
#define  ONLINE   _T("ONLINE")
#define  OFFLINE  _T("OFFLINE")
struct User
{
	CString m_loadName;
	CString m_password;
	CString m_callName;
	CString m_userState;
	CString m_userIp;
	CString m_userPort;
	User()
	{
		m_loadName = m_callName = m_password = m_userIp = m_userPort = _T("");
		m_userState = OFFLINE;
	}
};
class CMsg : public  CObject
{
    public:
		CString m_strText;
	    CString m_msgType;
		
		struct NomalMsg
		{
			CString who;
			CString toWho;
			CString msgItem;
			CString sndTime;
		} m_nomalMsg;
		struct SystemMsg
		{
			CString type;
			CString name;
			CString msgItem;
			CString sndTime;
		} m_systemMsg;

		struct LOADMSG
		{
			CString name;
			CString password;
		} m_loadMsg;
		
	public:
		CMsg(CString& preMsg);
		CMsg();
	    void Init();
 	    CString WhatType();
// 	//	void SetMsg();
// //	private:
 		void BuildNomal();
 		void BuildLoad();
 		void BuileSystem();

};
#endif