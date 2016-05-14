/********************************************************************
    FileName :  RzMemPool.h   
    Version  :  0.10
    Date     :	2010-3-9 17:11:48
    Author   :  С�һ�
    Comment  :

*********************************************************************/
#ifndef  __RZMEMPOOL_H__
#define  __RZMEMPOOL_H__
#include <assert.h>
#include "RzDReadAWriteLock.h"
#include <iostream>
_RzUsing(std)
/*****************************************************************************************************
  ����Ϊ�ڴ���࣬��������ʽ����ʵ��ջʽ��������ͷ���������Ƴ���
  ͬʱ�౾��ҲΪһ������Ľڵ�;m_pNext��¼��һ������
  �����κδ�С�ڴ涼���Գɹ����룬��ֻ���С��MaxSaveSize���ڴ�飬����ֱ��ɾ��

******************************************************************************************************/
_RzCFunBegin
_RzNameSpaceBegin(RzStd)
typedef struct _Node_
{
	unsigned int nLen;
	struct _Node_* next;
}Node;
const unsigned int NodeSize = sizeof(Node);
const unsigned int MaxSaveBlock =1024*1024*1;  //�������1M�ڴ�ʱ�ڴ�ز�����

class RZ_DLL_API CRzMemPool
{
public:
	CRzMemPool(const unsigned int& nDataSize,const unsigned int& nMaxSize=0):m_nBlockSize(nDataSize/*+NodeSize*/),
		m_nMaxSize(nMaxSize),m_pFirst(NULL),m_pNext(NULL),m_nInCount(0),m_nOutConut(0){};  
	~CRzMemPool()
	{
		m_Lock.EnterWrite();   
		{
			if (m_pFirst) DeleteNext(m_pFirst);
			m_pFirst = NULL;
			if (m_pNext) delete m_pNext;//ע�� ʵ���ǵݹ����
			m_pNext = NULL;
		}
		m_Lock.LeaveWrite();
		//cout<<"�ڴ�أ����С��"<<m_nBlockSize<<"�������"<<m_nInCount<<"�׳�������"<<m_nOutConut<<endl;
	};
public:
	void* GetBuf(const unsigned int &nSize)                    //��ָ����С���ڴ���л�ȡ�ڴ棨nSize��
	{
		void* pResutl = NULL;
		Node* pNewNode =NULL;

		if ( (nSize+NodeSize) <= m_nBlockSize)  //�ڴ���С > ���û������ڴ��С + ����ָ���С)
		{		                               //��ʾ������Ĵ�С��������������������ӱ������л�ȡ
			m_Lock.EnterWrite();
			{
				if (m_pFirst)                  //����ǿգ��������ȡ�ڵ�
				{                             //ע�ⲻ���ǿսڵ��������Ϊ�ձ�ʱ��˵������û���ڴ棬��Ӧ�ü���Ƿ�������������������粻����ֱ�ӷ���NULL					  				
					pNewNode = m_pFirst;
					m_pFirst = m_pFirst->next;
					pNewNode->next = NULL;				
					--m_nInCount;
					++m_nOutConut;
					pResutl = (char*)pNewNode + NodeSize;  //���û�ʹ���ڴ���ƣ���Ϊ�ڴ���ǰ��NodeSize��С���ڴ�����Node�еļ�¼
				}
				else if (0 == m_nMaxSize || m_nOutConut < m_nMaxSize)
				{
					pNewNode = (Node*)malloc(m_nBlockSize);
					if (pNewNode)
					{					
						pNewNode->nLen = m_nBlockSize;       //����м�¼���ڴ���С�������ͷ�ʱ�ع鵽��������
						pNewNode->next = NULL;				 
						pResutl = (char*)pNewNode + NodeSize;//���û�ʹ���ڴ���ƣ���Ϊ�ڴ���ǰ��NodeSize��С���ڴ�����Node�еļ�¼
						++m_nOutConut;	
					}
				}
			}
			m_Lock.LeaveWrite();
		}
		else   //�Ǳ�������������¸�������
		{
			m_Lock.EnterWrite();
			if (!m_pNext)
				m_pNext = new CRzMemPool(2*(m_nBlockSize/*-NodeSize*/),m_nMaxSize); //ע��Ϊ��������
			if(m_pNext)
				pResutl = m_pNext->GetBuf(nSize);
			m_Lock.LeaveWrite();
		}	
		return pResutl;
	};
	bool FreeBuf(void* pBuf,bool bDelete)                      //�ͷ��ڴ棬bDelete ָʾ�Ƿ�����ɾ���ڴ�	
	{
		if (!pBuf) return false;
		bool bResult = false;
		Node* pNode = GetNode(pBuf);
		if(!pNode) return false;

		if (m_nBlockSize == pNode->nLen)   //����������ڴ�
		{
			if (m_nBlockSize >= MaxSaveBlock || bDelete) //����ֱ��ɾ����������ֱ��ɾ��
			{
				free(pNode);
				--m_nOutConut;
			}
			else                                        //��������    
			{
				m_Lock.EnterWrite();//������д����             
				{
					pNode->next =  m_pFirst;
					m_pFirst = pNode;
				}
				m_Lock.LeaveWrite();
				--m_nOutConut;
				++m_nInCount;
			}
			bResult = true;   //ע������ֱ�ӷ���True ,��Ϊ�����϶��ɹ�
		}
		else //�Ǳ��������
		{
			m_Lock.EnterRead();   //�Ӷ�������m_pNext������
			{
				if (m_pNext)			
					bResult = m_pNext->FreeBuf(pBuf,bDelete);			
			}
			m_Lock.LeaveRead();
		}

		return bResult;
	}
	bool IsIn(const void* pBuf,const unsigned int &nNewSize)
	{
		assert(pBuf);
		if (0 >= nNewSize) return false;
		if ( (CRzMemPool::GetNode(pBuf)->nLen - NodeSize) >= nNewSize )
			return true;
		else 
			return false;
	}
	static unsigned int GetBufLen(const void* pBuf)
	{
		return GetNode(pBuf)->nLen;
	};
	void PrintInfo()
	{
		//�ݲ�ʵ��
	};
private:
	void DeleteNext(Node* pNext)                      //�ݹ�ɾ�������еĽڵ�
	{
		//��������˽�У����������������ã������������Դ˴����ü���
		if( !pNext) return;
		Node* pNode = pNext;
		Node* pTmpNode = NULL;
		while(1)
		{
			pTmpNode = pNode->next;
			free(pNode);
			--m_nInCount;
			if (!pTmpNode) break;
			pNode = pTmpNode;
		}
	}
	static Node* GetNode(const void* pBuf)
	{                               //��̬�������ü���
		assert(pBuf);
		Node* pTmpNode = (Node*)((char*)pBuf-NodeSize);
		return pTmpNode;
	};
private:
	const unsigned int  m_nBlockSize;                  //�ڴ���С  ��16KΪ��ʹ��С���Ա�������(������ֹ�޸�)
	const unsigned int  m_nMaxSize;                    //�����������ڴ��������
	DWORD               m_nOutConut;                   //�׳����ڴ�����
	DWORD               m_nInCount;                    //�ڴ���д洢���ڴ�����
	Node*         m_pFirst;                            //�������ͷ�ڵ�
	CRzDReadAWriteLock m_Lock;                         //�����������������
	CRzMemPool*   m_pNext;                             //���������һ������ָ��
};

class RZ_DLL_API CRzMemPoolMgr
{
public:
	CRzMemPoolMgr(unsigned int nMinSize = 8,const unsigned int nMaxSize = 0)
	{
		m_pHead = new CRzMemPool((nMinSize<16 ? nMinSize =16:nMinSize),nMaxSize) ; //����С�ڴ��4bytes ��ʹ��������ͷ��
	};
	~CRzMemPoolMgr()
	{
		if (m_pHead)
		{
			delete m_pHead;
			m_pHead = NULL;
		}
	};
public:
	void* GetBuf(unsigned int &nSize)
	{
		if (0 >= nSize) return NULL;

		void* pResult = NULL;
		if (m_pHead)
		{
			pResult = m_pHead->GetBuf(nSize);
		}
		return pResult;
	};                                             
	void* ReGetBuf(void* pOldBuf,unsigned int& nNewSize,bool bCopyOldData = true)
	{
		assert(pOldBuf);

		void* pResutl = NULL;
		if (0 >= nNewSize)
		{
			return pResutl;
		}	
		if (m_pHead->IsIn(pOldBuf,nNewSize))
		{
			pResutl = pOldBuf;
		}
		else
		{
			pResutl = m_pHead->GetBuf(nNewSize);
			if (pResutl && pOldBuf)
			{
				if(bCopyOldData)
					memcpy(pResutl,pOldBuf,CRzMemPool::GetBufLen(pOldBuf));
			}
		}
		return pResutl;
	}; 
	bool  Free(void* pBuf,bool bDelete = false)
	{
		if (!pBuf) return false;
		if(m_pHead)
			m_pHead->FreeBuf(pBuf,bDelete);
		return true;
	};
private:
	CRzMemPool* m_pHead;      //��������ͷ���
};
_RzNameSpaceEnd
_RzCFunEnd
#endif
