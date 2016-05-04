#ifndef PATHUTIL_H
#define PATHUTIL_H

namespace DuiLib
{
	class UILIB_API PathUtil
	{
	public:
		static CDuiString GetAppPath();	// ��ȡӦ�ó���ִ��·��
		static CDuiString GetCurAppName(BOOL bNoExt = TRUE);//
		static CDuiString GetCurDir();	// ��ȡӦ�ó���ǰĿ¼
		static CDuiString GetTempPath();	// ��ȡ��ǰϵͳ����ʱ�ļ��е�·��
		static CDuiString GetTempFileName(LPCTSTR lpszFileName);	// ��ȡ��ǰϵͳ����ʱ�ļ��е�·���µ�Ψһ��������ʱ�ļ���(ȫ·��)
		static CDuiString GetRandomFileName(LPCTSTR lpszPath, LPCTSTR lpszFileName);	// ��ȡ����ļ���(ȫ·��)

		static BOOL IsDirectory(LPCTSTR lpszPath);	// ���ָ��·���Ƿ�Ŀ¼
		static BOOL IsFileExist(LPCTSTR lpszFileName);	// ���ָ���ļ��Ƿ����
		static BOOL IsDirectoryExist(LPCTSTR lpszPath);	// ���ָ��Ŀ¼�Ƿ����
		static BOOL CreateDirectory(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
		static BOOL IsPathValid(LPCTSTR lpszPath); //·���Ƿ�Ϸ�

		static CDuiString CombinePath(LPCTSTR lpszPath1, LPCTSTR lpszPath2);//�ϲ�·��

		static CDuiString GetPathRoot(LPCTSTR lpszPath);	// ��ȡָ��·���ĸ�Ŀ¼��Ϣ
		static CDuiString GetDirectoryName(LPCTSTR lpszPath);	// ����ָ��·���ַ�����Ŀ¼��Ϣ
		static CDuiString GetFileName(LPCTSTR lpszPath); // ����ָ��·���ַ������ļ�������չ��
		static CDuiString GetFileNameWithoutExtension(LPCTSTR lpszPath);	// ���ز�������չ����·���ַ������ļ���
		static CDuiString GetExtension(LPCTSTR lpszPath);	// ����ָ����·���ַ�������չ��
		static CDuiString GetFullPath(LPCTSTR lpszPath);	// ����ָ�������·����ȡ����·��

		
	};
}

#endif//PATHUTIL_H