#pragma once
#include "../../YMusic.h"

class CSongInfo
{
private:
	UINT m_nLocalID;//����ID
	bool m_bLocal;//if bLocal is true then nSongID is 0;
	UINT m_nSongID;//����ID
	UINT m_nResourceID;//��ԴID
	UINT m_nAlbumID;//ר��ID
	UINT m_nArtistID;//����Id
	UINT m_nAudioLength;//ʱ��;
	UINT m_nPlayCount;//���Ŵ���

	long m_lAddTimeGMT;//���ʱ��
	long m_lLastModifyTimeGMT;//�ϴ��޸�ʱ��
	long m_lLastPlayTimeGMT;//�ϴβ���ʱ��

	int m_nFileType;//�ļ�����
	UINT m_nStartPos;//�ļ���ʼλ��
	UINT m_nFileSize;//�ļ���С

	CString	m_sSongName;//��������
	CString	m_sAlbumName;//ר������
	CString	m_sArtistName;//����������
	CString m_sRealArtistName;//ʵ������������
	CString m_sCoverLocalPath;
	CString m_sLrcLocalPath;
	CString m_sLocalPath;
	CString m_sCoverUrl;
	CString m_sLrcUrl;
	CString m_sListenFileUrl;
	CString m_sFileExt;
	CString m_sMD5;
	bool m_bAble;
	int m_nFlag;
	int m_nTag;
public:
	CSongInfo();
	CSongInfo(const CSongInfo& s);
	~CSongInfo();
public:
	bool operator== (const CSongInfo& other);
	bool IsLocal()const;
	void SetLocal(bool bLocal);
	bool IsEnable()const;
	void SetEnable(bool bEnable);
	UINT GetLocalId()const;
	void SetLocalId(UINT nId);
	UINT GetSongId()const;
	void SetSongId(UINT nSongId);
	UINT GetResourceId()const;
	void SetResourceID(UINT nResourceId);
	UINT GetAlbumId()const;
	void SetAlbumId(UINT nAlbumId);
	UINT GetArtistId()const;
	void SetArtistId(UINT nArtistId);
	UINT GetAudioLength()const;
	void SetAudioLength(UINT nAudioLength);
	UINT GetPlayCount()const;
	void SetPlayCount(UINT nPlayCount);
	void AddPlayCount();
	int GetFileType()const;
	void SetFileType(int nFileType);
	UINT GetFileSize()const;
	void SetFileSize(UINT nFileSize);
	UINT GetFileStartPos()const;
	void SetFileStartPos(UINT nStartPos);
	CString GetSongName()const;
	void SetSongName(const CString& sSongName);
	CString GetAlbumName()const;
	void SetAblumName(const CString& sAblumName);
	CString GetArtistName()const;
	void SetArtistName(const CString& sArtistName);
	CString GetRealArtistName()const;
	void SetRealArtistName(const CString& sRealArtistName);
	CString GetLocalPath()const;
	void SetLocalPath(const CString& sPath);
	CString GetCoverLocalPath()const;
	void SetCoverLocalPath(const CString& sPath);
	CString GetLrcLocalPath()const;
	void SetLrcLocalPath(const CString& sPath);
	CString GetListenFileUrl()const;
	void SetListenFileUrl(const CString& sUrl);
	void SetFileExt(const CString& sExt);
	CString GetFileExt() const;

	CString GetMD5()const;
	void SetMD5(const CString& sMD5);

	CString GetCoverUrl()const;
	void SetCoverUrl(const CString& sUrl);
	CString GetLrcUrl()const;
	void SetLrcUrl(const CString& sUrl);

	long GetAddTime()const;
	void SetAddTime(long lTime);
	long GetLastModifyTime()const;
	void SetLastModifyTime(long lTime);
	long GetLastPlayTime()const;
	void SetLastPlayTime(long nTime);

	int GetFlag()const;
	void SetFlag(int nFlag);

	int GetTag() const;
	void SetTag(int ntag);
};
typedef smart_pointer::SmartPtr<CSongInfo> spSongInfoT;

class songOrder  
{  
public:  
	bool operator()(spSongInfoT nod, spSongInfoT node)  
	{  
		return nod->GetLocalId() < node->GetLocalId();
	}  
}; 
class checkDuplic  
{  
public:  
	bool operator()(spSongInfoT nod, spSongInfoT node)  
	{  
		if (nod->IsLocal() && node->IsLocal())
		{
			return (nod->GetLocalPath() == node->GetLocalPath());
		}
		else if(!nod->IsLocal() && !node->IsLocal())
		{
			return (nod->GetListenFileUrl() == node->GetListenFileUrl());
		}
		else
		{
			return false;
		}
	}  
};  
/************************************************************************/
/*                                                                      */
/************************************************************************/
class CPlayListInfo
{
public:
	enum PlayListType
	{
		plt_sys = 0,//ϵͳ�б�,��Ĭ���б�;
		plt_auto,//�����б��Ƽ����Զ�����;
		plt_Roaming,//����;
		plt_user  //�û��Խ��б�;
	};
protected:
	UINT m_nLocalID;
	UINT m_nID;
	CString m_sName;
	CString m_sComment;
	PlayListType m_eType;
	bool m_bShow;
	int m_nFlag;
	int m_nTag;
public:
	CPlayListInfo();
	~CPlayListInfo();
	CPlayListInfo(const CString& sPlayListName,CPlayListInfo::PlayListType eType);

	UINT GetLocalId()const;
	void SetLocalId(UINT nId);
	UINT GetId()const;
	void SetId(UINT nId);
	CPlayListInfo::PlayListType GetListType()const;
	void SetListType(CPlayListInfo::PlayListType eType);
	CString GetName()const;
	void SetName(const CString& sName);
	CString GetComment()const;
	void SetComment(const CString& sComment);

	bool IsShow()const;
	void SetShow(bool bShow);

	int GetFlag()const;
	void SetFlag(int nFlag);

	int GetTag() const;
	void SetTag(int ntag);
};
typedef smart_pointer::SmartPtr<CPlayListInfo> spPlayListInfoT;
/************************************************************************/
/*                                                                      */
/************************************************************************/
class CFavInfo
{
public:
	enum FavType
	{	
		ft_album =1,//ר��;
		ft_collect,  //��ѡ��;
		ft_artist,//����;
		ft_song//����;
	};

private:
	UINT m_nId;
	CString m_sName;
	FavType m_eType;
public:
	CFavInfo();
	CFavInfo(FavType type,UINT nId,LPCTSTR pszName = NULL);
	~CFavInfo();

	UINT GetFavId()const;
	void SetFavId(UINT nId);
	CString GetFavName()const;
	void SetFavName(const CString& sName);
	FavType GetType()const;
	void SetType(FavType eType);

};

typedef smart_pointer::SmartPtr<CFavInfo> spFavInfoT;
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct SearchResult
{
	bool bNext;
	std::vector<spSongInfoT> SearchList;

	SearchResult()
	{
		bNext=false;
	}
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct MessageInfoCountT
{
	unsigned int nPmcount;
	unsigned int nMsgcount;
	unsigned int nFanscount;
	unsigned int nTime;
	unsigned int nSongCount; //�͸�
	unsigned int nFavCount; //��
	unsigned int nShareCount;//���ѷ��� 
	MessageInfoCountT()
	{
		nPmcount = 0;
		nMsgcount = 0;
		nFanscount = 0;
		nTime = 0;
		nSongCount = 0;
		nFavCount = 0;
		nShareCount = 0;
	}
};
typedef smart_pointer::SmartPtr<MessageInfoCountT> spMessageInfoCountT;
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct UserInfoT
{
	CString sUserID;
	CString sNickName;
	CString sArea;
	CString sAvaterUrl;
	CString sYear;
	unsigned int nFollowCount;
	unsigned int nFollowerCount;
	int nFlag;
	CString sSex;  //�Ա�
	CString sLevel;//�ȼ�
	CString sRegTime;
	unsigned int nCollect;
	CString sSignature; //ǩ��
	UserInfoT()
	{
		nFollowCount = 0;
		nFollowerCount = 0;
		nFlag = 0;
		nCollect = 0;
	}
	// 	UserInfoT(const UserInfoT& s)
	// 	{
	// 		*this = s;
	// 	}
};
struct LogonUserInfoT:public UserInfoT
{
	CString sLogonEmail;
	CString sPasswordMD5;
	bool bKeepLogged;
};
typedef smart_pointer::SmartPtr<LogonUserInfoT> spLogonUserInfoT;
typedef smart_pointer::SmartPtr<UserInfoT> spUserInfoT;
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct UserInfoListResult
{
	bool bNext;
	std::vector<spUserInfoT> userlist;

	UserInfoListResult()
	{
		bNext=false;
	}
};

struct WebServiceResult
{
	bool         isError;
	std::string  ErrorMsg;

	operator bool() const
	{
		return !isError;
	}
	CString Msg()
	{
		return em_utility::mci::utf8_2_CString(ErrorMsg.c_str());
	}
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
class CSynOperation
{
public:
	enum ObjectType
	{
		SOT_PlayList = 1 ,//�����б�;
		SOT_Song
	};
	enum OperateType
	{
		OT_Add = 1,//���
		OT_Update,//����
		OT_Del  //ɾ��
	};
	CSynOperation();
	CSynOperation(unsigned int nId,ObjectType eObType,OperateType eOpType);
	~CSynOperation();

private:
	unsigned int nAutoID;
	unsigned int nObjectID;
	ObjectType eObjType;
	OperateType eOperType;
	int nFlag;
public:
	unsigned int GetAutoID()const;
	void SetAutoID(unsigned int nID);
	unsigned int GetObjectID()const;
	void SetObjectID(unsigned int nID);
	ObjectType GetObjectType()const;
	void SetObjectType(ObjectType eType);
	OperateType GetOperateType()const;
	void SetOperateType(OperateType eType);
	int GetFlag()const;
	void SetFlag(int nflag);
};

typedef smart_pointer::SmartPtr<CSynOperation> spSynOperationT;
/************************************************************************/
/*                                                                      */
/************************************************************************/
extern unsigned int const MAX_USER_LIST;
extern unsigned int const MAX_FAV_NOTICE;
/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace ConfigEX
{
	extern const TCHAR KEEPMOST_TOP[];	
	extern const TCHAR VOLUME[];
	extern const TCHAR LOCKDESKLRC[];
	extern const TCHAR NOWARN_REMOVELIST[];
	extern const TCHAR NOWARN_REMOVESONG[];
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
enum ProtocolIndex{
	PI_Empty = 1,
	PI_GetOp,
	PI_RegExt,
	PI_UnRegExt,
	PI_Run,
	PI_UnRun,
	PI_RegUrlProto,
	PI_UnRegUrlProto,
	PI_END
};

extern TCHAR const XIAMI_HOST[];
extern TCHAR const SERVER_URL[];

/************************************************************************/
/*                                                                      */
/************************************************************************/

#define  RegURL_KEY				 _T("regURL")
#define  ForGetPasswordURL_KEY   _T("forGetPasswordURL")
#define  SinaLoginURL_KEY		 _T("sinaLoginURL")
#define  QQLoginURL_KEY			 _T("qqLoginURL")
#define  WebLoginSucceedURL_KEY  _T("webLoginSucceedURL")


