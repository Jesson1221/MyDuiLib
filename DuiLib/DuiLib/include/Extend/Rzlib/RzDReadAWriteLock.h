/********************************************************************
    FileName :  RzMultiReadSingleWriteLock.h   
    Version  :  0.10
    Date     :	2010-1-25 18:42:25
    Author   :  С�һ�
    Comment  :  �����д��

*********************************************************************/
#ifndef __RZDREADAWRITELOCK_H__
#define __RZDREADAWRITELOCK_H__
#include "RzType.h"
namespace RzStd
{
	typedef struct _RZ_InsideLock_
	{
		int nReadCount;
		bool bWriteFlag;
		RzLock rzLock;
	}SInsideLock; //�ڲ���

	class RZ_DLL_API CRzDReadAWriteLock
	{
	public:
		CRzDReadAWriteLock(void)
		{
			::InitializeCriticalSection(&m_Lock.rzLock);
			m_Lock.nReadCount = 0;
			m_Lock.bWriteFlag = false;
		};
		virtual ~CRzDReadAWriteLock(void)
		{
			::EnterCriticalSection(&m_Lock.rzLock);
			::LeaveCriticalSection(&m_Lock.rzLock);
			::DeleteCriticalSection(&m_Lock.rzLock);
		};
	public:
		void EnterWrite()
		{
			while(1)
			{
				::EnterCriticalSection(&m_Lock.rzLock);
				if ( !m_Lock.bWriteFlag ) //��дʱ��������д���£�д�õ�����Ȩ
				{
					m_Lock.bWriteFlag = true;
					::LeaveCriticalSection(&m_Lock.rzLock); 
					goto _Start_Write;
				}
				//	//cout<<::GetCurrentThreadId()<<"��д��д�ȴ�...\n"; 
				::LeaveCriticalSection(&m_Lock.rzLock);
				Sleep(0/*1*/);
			}
_Start_Write:
			while(GetReadCount())//�ȴ���������Ϊ 0
			{
				/*//cout<<"��ǰ�������У�"<<GetReadCount()<<endl;	*/
				Sleep(/*1*/0);
			}
		};
		void LeaveWrite()
		{
			::EnterCriticalSection(&m_Lock.rzLock);
			//	//cout<<::GetCurrentThreadId()<<"д���\n"; 
			m_Lock.bWriteFlag = false;
			::LeaveCriticalSection(&m_Lock.rzLock);
		};	
		int EnterRead()
		{
			int n=0;
			while(1)
			{
				::EnterCriticalSection(&m_Lock.rzLock);
				if (!m_Lock.bWriteFlag) //���߳���д
				{		
					n = ++m_Lock.nReadCount;
					goto _Start_Read;
				}
				//	//cout<<::GetCurrentThreadId()<<"��д�����ȴ�...\n"; 
				::LeaveCriticalSection(&m_Lock.rzLock);
				Sleep(0/*1*/);
			}
_Start_Read:
			//	//cout<<::GetCurrentThreadId()<<"��д,�����\n"; 
			::LeaveCriticalSection(&m_Lock.rzLock);
			return n;
		};
		int LeaveRead()
		{
			int n = 0;
			::EnterCriticalSection(&m_Lock.rzLock);
			if ( 0 < m_Lock.nReadCount )
			{
				n = --m_Lock.nReadCount;
			}
			//	//cout<<::GetCurrentThreadId()<<"�����\n"; 
			::LeaveCriticalSection(&m_Lock.rzLock);
			return n;
		};
		int GetReadCount()
		{
			int n =0;
			::EnterCriticalSection(&m_Lock.rzLock);
			n = m_Lock.nReadCount;
			::LeaveCriticalSection(&m_Lock.rzLock);
			return n;
		};
		bool IsWrite()
		{
			bool bVar = false;
			::EnterCriticalSection(&m_Lock.rzLock);
			bVar = m_Lock.bWriteFlag;
			::LeaveCriticalSection(&m_Lock.rzLock);
			return bVar;
		};
	private:
		SInsideLock m_Lock;
	};
};
#endif // RzMultiReadSingleWriteLock_h__

