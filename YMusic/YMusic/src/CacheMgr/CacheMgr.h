#pragma once

/************************************************************************
* �������ļ�
*   ����ļ�
*   �����ļ�
*   ר��ͼƬ�ļ�
*   Web�ļ�
***********************************************************************/
#include "../../YMusic.h"

class CCacheMgr
{
public:
	CCacheMgr(void);
	~CCacheMgr(void);
public:
	void Init(CString sCachePath);
	size_t GetAllCatchSize();
	void ClearAllCatch();
	void StatSize(size_t nNewFileSize);

	CString GetLrcPath();
	CString GetSongPath();
	CString GetImagePath();
	CString GetWebPath();

private:
	size_t GetFolderSize(CString sPath);
	void CleanFolder(CString sPath);
	void StatFolderSize(size_t nNewFileSize);

	size_t m_nTotalCacheSize;
	CString m_sCachePath;
//	spOperationQueueT m_pQueue;

	CString m_sLrcPath;
	CString m_sSongPath;
	CString m_sImagePath;
	CString m_sWebPath;
};


