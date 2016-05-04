#pragma once

#include "WebServiceCatch.h"

#include "../../YMusic.h"

namespace url
{
	typedef std::string UTF8STR;
	typedef UTF8STR     URLSTR;
    
enum emShareObjT
{
	SOT_SONG = 32,
	SOT_ALBUM,
	SOT_ARTIST,
	SOT_AMBUS
};

    enum emRequestT
	{
		WSRT_NULL,
		//��¼
		WSRT_LOGIN,
		WSRT_WEBLOGIN,
		//�ղ�
		WSRT_FAVORITE,
		WSRT_ADD_FAVORITE,
		WSRT_DEL_FAVORITE,
		//����
		WSRT_SHARE,

		//����ͳ��
		WSRT_PLAYLOG,

		//�����б��ҵ��б�
		WSRT_GET_LIST,
		WSRT_NEW_LIST,
		WSRT_DEL_LIST,
		WSRT_RENAME_LIST,
		WSRT_CHANGE_STATUS,
		WSRT_LIST_GET_SONGS,
		WSRT_LIST_ADD_SONGS,
		WSRT_LIST_DEL_SONGS,
		WSRT_DETAIL_INFO,
		WSRT_LIST_CLEAR,
		
		//�����б�;
		WSRT_GET_ROAMING,
		//ƥ�����;
		WSRT_MATCH_SONG,
		//��ǩ�б�;
		WSRT_GET_TAG_LIST,
		WSRT_GET_TAG_SONGS,	
		//�ֿ��Ƽ�;
		WSRT_LIB_RECOMMEND_SONGS,
		WSRT_LIB_RECOMMEND_ALBUMS,
		//
		WSRT_SEARCH,
		WSRT_SEARCHMARK,
		WSRT_ATTENTIONLIST,
		WSRT_FANCELIST,
		WSRT_RECOMMENDWINDOW,
		WSRT_CANCELATTENTION,
		WSRT_PRAISE,
		WSRT_ADDATTENTION,
		WSRT_SENDSONG,
		WSRT_GETALLFRIENDS,
		WSRT_REPLYCOMMENT,
		WSRT_REPLYSENDSONG,
		WSRT_FRIENDUSERINFO,
		WSRT_MESSAGEINFOCOUNT,

		WSRT_RECOMMENDSENDSONG,
		WSRT_RECOMMENDGOOD,
		WSRT_RECOMMENDSHARE,
		WSRT_RECOMMEDNUPDATE
	}; 

    class CRequest
    {
    public:
//    typedef boost::function<void (CRequest*,void*)> ResponderT;
	  typedef void(*ResponderT)(CRequest*,void*); 
      CRequest(emRequestT requestType,const URLSTR& paths,const URLSTR& params);
      CRequest(emRequestT requestType,const URLSTR& paths,const URLSTR& params,ResponderT responder);
      ~CRequest();
        
      emRequestT GetRequestType() const;
      URLSTR GetPaths() const;
	  URLSTR GetParams() const;   

      HWND GetHwnd() const;
      void SetHwnd(HWND h); 

      DWORD GetTag() const;
      void SetTag(DWORD dwTag);

      CatchStrategyType GetCatchStrategyType() const;
	  void SetCatchStrategyType(CatchStrategyType nType);

      bool IsCatched() const;
	  void SetCatched(bool bCatch);

      bool IsTimeOut() const;
      void SetTimeOut(bool b);

	  int GetCreateTime();

      bool HasReponder() const;
      void SetReponder(ResponderT responder);
	  void Response(void* pdata);
    protected:
        ResponderT              _responder;
        HWND                    _hwnd;
		int                     _tCreate;
		URLSTR                  _sPaths;
		URLSTR                  _sParams; 
		emRequestT              _requestType;
        bool                    _bIsFromCatch;
		CatchStrategyType       _nStrategyType;
        bool                    _isTimeOut;
        DWORD                   _dwTag;
    };
	
	class Requester
	{
	private:
		const static std::string              _sAPI_URL;
		const static std::string              _sAPI_KEY;
		const static std::string              _sAPI_SECRET;
	public:
		Requester();
		~Requester();

		static std::string GenSigUrl( const std::string& sMethod, const std::vector<std::pair<std::string,std::string> >& v);
		static std::string GenSigUrl( const CString& sMethod, const std::vector<std::pair<CString,CString> >& v);
		static std::string GenSigUrlEX( const std::string& sMethod, const std::vector<std::pair<std::string,std::string> >& v);
		static std::string GenSigUrlEX(const CString& sMethod, const std::vector<std::pair<CString,CString> >& v);
		//��¼
		static CRequest* MakeLogin(const UTF8STR& sUserName,const UTF8STR& sPasswordMd5);
		static CRequest* MakeLogin(LPCTSTR pszUserName,LPCTSTR pszPasswordMd5);
		static CRequest* MakeLogin(const UTF8STR& sToken);
		static CRequest* MakeLogin(LPCTSTR pszToken);

		//����
		//static CRequest* MakeShare(uint nSendUserId,const UTF8STR& sCommenMsg,uint nObjId,emShareObjT objType = SOT_SONG);
		static CRequest* MakeShare(uint nSendUserId,LPCTSTR lpszCommentMsg,uint nObjId,emShareObjT objType = SOT_SONG);

		//����ͳ��
		static CRequest* MakePlayLog(uint nUserId,uint nSongId);
		//�ҵ��б�
	    static CRequest* MakeGetList(uint nUserId);
		static CRequest* MakeNewList(uint nUserId,uint nListId,const CString& sName,const CString& sSongs = CString(),bool bShow = true);
		static CRequest* MakeNewList(uint nUserId,uint nListId,const CString& sName,const std::vector<spSongInfoT>& songs,bool bShow = true);
	    static CRequest* MakeDelList(uint nUserId,uint nListId,bool bAll = true);
	    static CRequest* MakeReNameList(uint nUserId,uint nListId,const CString& sName);
		static CRequest* MakeChangeListStatus(uint nUserId,uint nListId,bool bShow);
	    static CRequest* MakeGetSongsFromList(uint nUserId,uint nListId,uint nPage,uint nType);
	    static CRequest* MakeAddSongToList(uint nUserId,uint nListId,const CString& sSongs);
	    static CRequest* MakeDelSongFromList(uint nUserId,uint nListId,const CString& sSongs);
	    static CRequest* MakeClearList(uint nUserId,uint nListId);

		//�����б�;
		static CRequest* MakeGetRoamingSongs(uint nSongId,uint nListId);

		//��ǩ�б�
		static CRequest* MakeTagList(bool bLogin,const CString& sData,uint nCount = 1);
		static CRequest* MakeTagList(bool bLogin,const std::vector<std::pair<int,int> >& DataArray,uint nCount = 1);
		static CRequest* MakeGetTagListSongs(uint nType,uint nListWebId,uint nUserId = 0);

		//ƥ�����;
		static CRequest* MakeMatchSong(std::vector<spSongInfoT> songs);
		//�ղ�����;
		static CRequest* MakeGetFavData(uint nUserId,uint nPageIndex,uint nType);
		static CRequest* MakeAddFav(uint nUserId,uint nId,CFavInfo::FavType eType);
		static CRequest* MakeDelFav(uint nUserId,uint nId,CFavInfo::FavType eType);
		//������ϸ��Ϣ;
		static CRequest* MakeDetailInfo(const CString& sIdArray,CFavInfo::FavType eType);
		static CRequest* MakeDetailInfo(const std::vector<uint>& IdArray,CFavInfo::FavType eType);

		//���ְ�
		static CRequest* MakeMusicPacketDetailInfo(uint nUserId,uint nId,uint nType,uint nSonglimit,uint nSongPage,uint nLimit,uint nPage);

		//�ֿ��Ƽ�����;
		static CRequest* MakeGetUnloginRecommendSongs(const CString& sPlayRecordData,uint nRetCount);
		static CRequest* MakeGetLoginRecommendSongs(uint nUserId,uint nRetCount);

		static CRequest* MakeGetUnloginRecommendAlbums(const CString& sPlayRecordData,uint nRetCount);
		static CRequest* MakeGetLoginRecommendAlbums(uint nUserId,uint nRetCount);
	};
}
