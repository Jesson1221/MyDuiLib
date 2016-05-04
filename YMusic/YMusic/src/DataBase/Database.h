#pragma once

#include "../../YMusic.h"
#include "CppSQLite3.h"
#pragma comment(lib,"sqlite3cpp.lib")
#include <vector>


	class  CDatabase
	{
	public:
		static const int  SQLERROR = -1;
		static const int  DBVersion = 0;
		static const int  BackupDBRate = 60*60*24;
		static const char DicTableName[]; 
		static const CString DBVersionKey;
		static const CString LastBackupKey;
		typedef CppSQLite3Query     SQLResult;
		typedef CppSQLite3Buffer    SQLBuffer;

		CDatabase():_pDB(NULL){}
		virtual ~CDatabase(){ CloseDB(); }

		bool OpenDB(CString sFileName);
		bool CloseDB();
		bool BackupDB(CString sFileName);
		bool IsOpen() const {return !!_pDB;}
		int GetDBVersion();

		bool GetDictValue(CString sKey, CString &sValue); //if sKey is exsited return true,if not exsit return false
		bool GetDictValue(CString sKey,int& nValue);
		bool GetDictValue(CString sKey,DWORD& dwValue);
		bool GetDictValue(CString sKey,bool& nValue);
		bool UpdateDictValue(CString sKey, CString sValue); //if Key is exsited update it and  return true,if not exsit return false
		bool UpdateDictValue(CString sKey,int nValue);
		bool UpdateDictValue(CString sKey,DWORD dwValue);
		bool UpdateDictValue(CString sKey,bool nValue);
		bool InsertDict(CString sKey, CString sValue);//if Key is exsited return false ,if not exsit insert new one and return true
        bool InsertDict(CString sKey,int nValue);  
		bool InsertDict(CString sKey,DWORD dwValue);
        bool InsertDict(CString sKey, bool nValue);
        bool DeleteDict(CString sKey);

	protected:
		int ExecScalar(const char* fmt,...);
		int ExecSql(const char* fmt,...);
		SQLResult QuerySql(const char* fmt,...);
	public:
		bool IsExistTable(const char* tablename);
		bool DeleteTable(const char* tablename);
		bool BeginTransaction();
		bool Commit();
		bool RollBack();
	protected:
		virtual bool OnCreateTables() = 0;
		virtual bool OnUpdateTables(int oldVer,int newVer) = 0;
	private:
		CppSQLite3DB * _pDB;
	};
	typedef smart_pointer::SmartPtr<CDatabase> spCDatabaseT;


	class CGlobalDBase : public CDatabase
	{
	public:
		static const char UserInfoTableName[];
		static const CString LastLogonUserKey;
	public:
		//�õ����б�����¼�����û�
		bool GetAllUserInfo(std::vector<spLogonUserInfoT> &UserInfoList);
		//�õ�ָ��ID�û�
		spLogonUserInfoT GetUserInfo( const char* sUserID);
		//����û�
		bool AddUserInfo(spLogonUserInfoT spUserInfo);
		//�����û�
		bool UpdateUserInfo(spLogonUserInfoT spUserInfo);
		//ɾ���û�
		bool RemoveUserInfo(const char* sUserID);
		bool RemoveUserInfo(unsigned int nUserID);
		//���һ����¼�û�
		spLogonUserInfoT GetLastUserInfo();
		bool UpdateLastUserInfo(spLogonUserInfoT spUserInfo);

		bool GetAllPlayLists(std::vector<spPlayListInfoT> &PlayList);
		bool AddPlayList(spPlayListInfoT spListInfo);
		bool UpdatePlayList(spPlayListInfoT spListInfo);
		bool RemovePlayList(unsigned int nPlayListID);
	public:

	protected:
		bool CreateUserTable();
	protected:
		virtual bool OnCreateTables();
		virtual bool OnUpdateTables(int oldVer,int newVer);
	};
	typedef smart_pointer::SmartPtr<CGlobalDBase> spGlobalDBaseT;

	class CUserDBase:public CDatabase
	{
	public:
		static const char PlayListTableName[];//�б�                  --�洢�û����������б�
		static const char SongListTableName[];//������                --ÿ���б���Ӧһ��������
		static const char FavoritesTableName[];//�ղ�				  --�û��ղر�������ͬ��
		static const char PlayRecordTableName[];//���ż�¼			  --�û����ز��ż�¼
		static const char DetailPlayRecordTableName[];//��ϸ���ż�¼
		static const char LocalMusicPacketTableName[];//�������ְ�
		static const char OperationTableName[];//����				  --�û�������ʷ
	public:	
		// --��ȡָ��Id���б���Ϣ
		bool GetPlayList(spPlayListInfoT& PlayListInfo,unsigned int nPlayListID);
		// --��ȡ�����б���Ϣ
		bool GetAllPlayLists(std::vector<spPlayListInfoT> &PlayList);
		// --��ȡָ�����͵��б�
		bool GetAllPlayListsByType(std::vector<spPlayListInfoT> &PlayList,unsigned int nType);
		// --����û��б�
		bool AddPlayList(spPlayListInfoT spListInfo);
		// --�����б���Ϣ
		bool UpdatePlayList(spPlayListInfoT spListInfo);
		// --�Ƴ�ָ���б�
		bool RemovePlayList(unsigned int nPlayListID);
		// --������ָ���б�
		bool RenamePlayList(unsigned int nPlayListID,CString newName);
		// --���ĳ�����Ƶ��б��Ƿ����
		bool IsPlayListExists(CString sPlayListName);
		// --�����б����ƻ�ȡ�б���Ϣ
		bool GetPlayListByName(CString sPlayListName,spPlayListInfoT& PlayListInfo);

		// --��ȡָ���б�Id�ĸ����б�
		bool GetPlayListSongs(std::vector<spSongInfoT> &SongList,unsigned int nPlayListID = 0  );
		// --��Ӹ�����ָ���б�
		bool AddSongsToPlayList(spSongInfoT spSongInfo, unsigned int nPlayListID = 0);
		bool AddSongToPlayList(CString songPath,unsigned int nPlayListID,spSongInfoT& spSongInfo);
		bool AddSongsToPlayList(std::vector<spSongInfoT> &SongList, unsigned int nPlayListID = 0);
		// --����ָ���б�Id�ĸ�����Ϣ
		bool UpdatePlayListSongInfo(spSongInfoT spSongInfo, unsigned int nPlayListID = 0);
		bool UpdatePlayListSongInfo(std::vector<spSongInfoT> SongArray,unsigned int nPlayListID = 0);
		bool UpdatePlayListSongPath(spSongInfoT spSongInfo, unsigned int nPlayListID = 0);
		// --ɾ��ָ���б�Id�ĸ���
		bool RemovePlayListSongs(spSongInfoT spSongInfo, unsigned int nPlayListID = 0);
		bool RemovePlayListSongs(std::vector<spSongInfoT> &SongList, unsigned int nPlayListID = 0);
		// --���ָ���б�Id�ĸ���
		bool RemoveAllPlayListSongs( unsigned int nPlayListID = 0);
		// --ɾ��ָ���б�Id�ĸ����б�
		bool DeletePlayList( unsigned int nPlayListID = 0);

		// --�ҵ��ղ�
		bool CreateFavTable();
		bool AddFavorites(spFavInfoT spFavInfo);
		bool AddFavorites(std::vector<spFavInfoT> &FavList);
		bool RemoveFavorites(unsigned int nId,unsigned int nType);
		bool RemoveFavorites(std::vector<spFavInfoT> &FavList);
		bool RemoveAllFavorites();
		bool GetAllFavorites(std::vector<spFavInfoT> &FavList);
	
		// --�ҵĲ��ż�¼
		bool AddPlayDetailRecord(unsigned int nSongId,unsigned int nSecond,bool bSkip);
		bool GetRecentFavRecord(std::vector<spFavInfoT> &FavList);
		bool GetPlayRecord(std::vector<std::pair<int,int> >& DataArray,bool bSkipRecord);
	
		// --�������ְ��ӿ�;
		bool GetLocalMusicPacket(unsigned int nPlayListLocalId,std::vector<std::pair<UINT,UINT> >& PacketArray,UINT nStartPos,UINT nLimit,bool bSong);
		bool AddMusicPacket(unsigned int nPlayListLocalId,const std::pair<UINT,UINT>& Packet);
		bool AddMusicPacket(unsigned int nPlayListLocalId,const std::vector<std::pair<UINT,UINT> >& PacketArray);
		bool RemoveMusicPacket(unsigned int nPlayListLocalId,const std::pair<UINT,UINT>& Packet);
		UINT GetMusicPacketCount(unsigned int nPlayListLocalId,bool bSong);
		
		// --Operation�����;
		bool CreateOperationTable();
		bool GetAllOperation(std::vector<spSynOperationT>& OperationArray);
		bool AddOperation(spSynOperationT spSynOperation);
		bool DelOperation(spSynOperationT spSynOperation);
	protected:
		// --����Ĭ�ϲ����б�[�����б�](ϵͳ����)
		bool AddDefaultPlayList();
		// --�����ҵ��ղ��б�[�ҵ��ղ�](ϵͳ����)
		bool AddDefaultFav();
		bool CreateTablePlayLists();
		bool CreateTableSongLists(const char* sPlayTableName);
	protected:
		virtual bool OnCreateTables();
		virtual bool OnUpdateTables(int oldVer,int newVer);
	};
	typedef smart_pointer::SmartPtr<CUserDBase> spUserDBaseT;