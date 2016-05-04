#include "StdAfx.h"
#include "mainwindow.h"
#include "../userinfo/user.h"
#include "../login/login.h"

namespace sysbtn
{//ϵͳ����ť
	const TCHAR* const kMinBtn = _T("minbtn");//��С��
	const TCHAR* const kMaxBtn = _T("maxbtn");//���
	const TCHAR* const kCloseBtn = _T("closebtn");//�ر�
	const TCHAR* const kRestoreBtn = _T("restorebtn");//��ԭ
};
namespace toppage
{//������
	const TCHAR* const kLogo = _T("logo");//�û�logo
	const TCHAR* const kNickName = _T("nickname");//�û��ǳ�
	const TCHAR* const kMyState = _T("mystate");//�û�״̬
	const TCHAR* const kSignatureBtn = _T("signaturetip");//����ǩ����ť
	const TCHAR* const kSignature = _T("signature");//����ǰ��༭��
	const TCHAR* const kWeather = _T("weather");//������ť
	const TCHAR* const kMyZone = _T("myZone");//�ҵĿռ�
	const TCHAR* const kMyEmail = _T("myEmail");//�ҵ�����
	const TCHAR* const kMyXiaoYou = _T("myXiaoYou");//�ҵ�У��
	const TCHAR* const kMySoSo = _T("mySoSo");//����
	const TCHAR* const kMsgBox = _T("msgbox");//��Ϣ����
	const TCHAR* const kSkinBtn = _T("bkskinbtn");//Ƥ��
	const TCHAR* const kColorBtn = _T("colorskinbtn");//������ɫ
	const TCHAR* const kSearchTip = _T("search_tip");//
	const TCHAR* const kSearchEdit = _T("search_edit");//������
	const TCHAR* const kSearchBtn = _T("searchbtn");//������ť
};
namespace tabpage
{
	const TCHAR* const kFriendOpt = _T("friendopt");
	const TCHAR* const kGroupOpt = _T("groupopt");
	const TCHAR* const kBlogOpt = _T("microblogopt");
	const TCHAR* const kRecentOpt = _T("recentfriendopt");
	const TCHAR* const kTab = _T("tabs");
	const TCHAR* const kFriends = _T("friends");
	const TCHAR* const kGroups = _T("groups");
	const TCHAR* const kMicroblog = _T("microblog");
	const TCHAR* const kRecent = _T("recentfriends");
};
namespace bottompage
{
	const TCHAR* const kWireless = _T("cellphone");
	const TCHAR* const kGames = _T("games");
	const TCHAR* const kPets = _T("pets");
	const TCHAR* const kLive = _T("audio_live");
	const TCHAR* const kMusic = _T("music");
	const TCHAR* const kMainMeun = _T("MainMenu");
	const TCHAR* const kTools = _T("tools");
	const TCHAR* const kSafe = _T("safe");
	const TCHAR* const kMessage = _T("message");

	const TCHAR* const kAppGrid = _T("AppGrid");
	const TCHAR* const kAppHome = _T("AppHome");
};
CMainWindow* theApp = NULL;
CMainWindow::CMainWindow()
{
	InitAllVariable();
}
CMainWindow::~CMainWindow()
{}
LPCTSTR CMainWindow::GetWindowClassName() const
{
	return _T("QQMainWindow");
}
CDuiString CMainWindow::GetSkinPath()
{
	return CPaintManagerUI::GetInstancePath();
}
CDuiString CMainWindow::GetSkinFolder()
{
	return _T("QQ\\skin\\0");
}
UILIB_RESOURCETYPE CMainWindow::GetResourceType() const
{
	return UILIB_ZIP;
}
CDuiString CMainWindow::GetZIPFileName() const
{
	return _T("0.zip");
}

CControlUI* CMainWindow::CreateControl(LPCTSTR pstrClass)
{
	try
	{
		if(_tcscmp(pstrClass,_T("FriendList"))==0)
			return new CGroupListUI(*(GetPaintMgr()));
		else if(_tcscmp(pstrClass,_T("GroupList"))==0)
			return new CGroupListUI(*(GetPaintMgr()));
		else if(_tcscmp(pstrClass,_T("MicroBlog"))==0)
			return new CListUI();
		else if(_tcscmp(pstrClass,_T("RecentFriend"))==0)
			return new CTreeViewUI();
		else 
			return NULL;
	}
	catch (...)
	{
	}
	return NULL;
}
template<typename T>
void CMainWindow::FindControl(T& pctrl,LPCTSTR pstrName) const
{
	pctrl = static_cast<T>(GetPaintMgr()->FindControl(pstrName));
}
void CMainWindow::InitAllVariable()
{
	m_pTabSwitch = NULL;
	m_pFriendTree = NULL;
	m_pGroupTree = NULL;
	m_pRecentFriend = NULL;
}
void CMainWindow::Notify( TNotifyUI &msg )
{
	DUI__Trace(msg.sType);
	if (msg.sType==_T("windowinit"))
	{
		OnInitWindow(msg);
	}
	else if (msg.sType==_T("click"))
	{
		OnClick(msg);
	}
	else if (msg.sType==_T("selectchanged"))
	{
		OnSelectChanged(msg);
	}
	else if (msg.sType==_T("itemactivate"))
	{
		OnItemActive(msg);
	}
	else if (msg.sType==_T("itemclick"))
	{
		OnItemClick(msg);
	}
	else if (msg.sType==_T("menu"))
	{
		OnMenu(msg);
	}
	else if (msg.sType==_T("killfocus"))
	{
		OnKillFocus(msg);
	}
	else if (msg.sType==_T("return"))
	{
		OnReturn(msg);
	}
}
void CMainWindow::OnInitWindow(TNotifyUI& msg)
{
	CPaintManagerUI* pPaintMgr = GetPaintMgr();
	ASSERT(pPaintMgr);
	FindControl(m_pTabSwitch,tabpage::kTab);
	ASSERT(m_pTabSwitch);
	FindControl(m_pFriendTree,tabpage::kFriends);
	ASSERT(m_pFriendTree);
	FindControl(m_pGroupTree,tabpage::kGroups);
	ASSERT(m_pGroupTree);
	FindControl(m_pRecentFriend,tabpage::kRecent);
	ASSERT(m_pRecentFriend);

	UserInfo user;
	user.ID("1001");
	user.NickName("�ҵĺ���");
	Node* parent = m_pFriendTree->AddRoot(user);
// 	user.ID("1002");
// 	user.Logo("file='userlogo/man_big.png' corner='5,5,5,5'");
// 	user.NickName("������");
// 	user.Signature("libyyu@qq.com");
// 	m_pFriendTree->AddNode(user,parent);
	
	user.ID("1003");
	user.NickName("��ӵ�е�Ⱥ");
	Node* parent2 = m_pGroupTree->AddRoot(user);
// 	user.ID("1004");
// 	user.NickName("�������1001��");
// 	user.Logo("file='list/default.png' corner='5,5,5,5'");
// 	user.Signature("�人�Ƽ���ѧ�������2010��");
//	m_pGroupTree->AddNode(user,parent2);
	user.ID("1004");
	user.NickName("�ҵ�������");
	Node* parent3 = m_pGroupTree->AddRoot(user);

}
void CMainWindow::OnClick(TNotifyUI& msg)
{
	if(msg.pSender->IsName(sysbtn::kCloseBtn))
	{
		OnExit(msg);
	}
	else if (msg.pSender->IsName(sysbtn::kMaxBtn))
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return;
	}
	else if (msg.pSender->IsName(sysbtn::kRestoreBtn))
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; 
	}
	else if (msg.pSender->IsName(sysbtn::kMinBtn))
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return;
	}
	else if (msg.pSender->IsName(toppage::kSignatureBtn))
	{
		msg.pSender->SetVisible(false);
		CRichEditUI* signature = static_cast<CRichEditUI*>(GetPaintMgr()->FindControl(toppage::kSignature));
		if (signature != NULL)
		{
			signature->SetText(msg.pSender->GetText());
			signature->SetVisible(true);
			signature->SetFocus();
			signature->SetSelAll();
		}
	}
}
void CMainWindow::OnSelectChanged(TNotifyUI& msg)
{
	if (msg.pSender->IsName(tabpage::kFriendOpt))
	{
		m_pTabSwitch->SelectItem(0);
	}
	else if (msg.pSender->IsName(tabpage::kGroupOpt))
	{
		m_pTabSwitch->SelectItem(1);
	}
	else if(msg.pSender->IsName(tabpage::kBlogOpt))
	{
		m_pTabSwitch->SelectItem(2);
	}
	else if (msg.pSender->IsName(tabpage::kRecentOpt))
	{
		m_pTabSwitch->SelectItem(3);
	}
}
void CMainWindow::OnItemActive(TNotifyUI& msg)
{

}
void CMainWindow::OnItemClick(TNotifyUI& msg)
{
	if (m_pTabSwitch != NULL)
	{
		if (m_pTabSwitch->GetCurSel() == 0)
		{
			if ((m_pFriendTree != NULL) &&  m_pFriendTree ->GetItemIndex(msg.pSender) != -1)
			{
				if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
				{
					Node* node = (Node*)msg.pSender->GetTag();

					if (m_pFriendTree ->CanExpand(node))
					{
						m_pFriendTree ->SetChildVisible(node, !node->data().child_visible_);
					}
				}
			}
		}
		else if (m_pTabSwitch->GetCurSel() == 1)
		{
			if ((m_pGroupTree != NULL) &&  m_pGroupTree ->GetItemIndex(msg.pSender) != -1)
			{
				if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
				{
					Node* node = (Node*)msg.pSender->GetTag();

					if (m_pGroupTree ->CanExpand(node))
					{
						m_pGroupTree ->SetChildVisible(node, !node->data().child_visible_);
					}
				}
			}
		}
	}
}
void CMainWindow::OnKillFocus(TNotifyUI& msg)
{
	if (_tcsicmp(msg.pSender->GetName(), toppage::kSignature) == 0)
	{
		msg.pSender->SetVisible(false);
		CControlUI* signature_tip = GetPaintMgr()->FindControl(toppage::kSignatureBtn);
		if (signature_tip != NULL)
		{
			CRichEditUI* signature = static_cast<CRichEditUI*>(msg.pSender);
			if (signature != NULL)
				signature_tip->SetText(signature->GetText());
			signature_tip->SetVisible(true);
		}
	}
}
void CMainWindow::OnReturn(TNotifyUI& msg)
{
	if (_tcsicmp(msg.pSender->GetName(), toppage::kSignature) == 0)
	{
		msg.pSender->SetVisible(false);
		CControlUI* signature_tip = GetPaintMgr()->FindControl(toppage::kSignatureBtn);
		if (signature_tip != NULL)
		{
			CRichEditUI* signature = static_cast<CRichEditUI*>(msg.pSender);
			if (signature != NULL)
				signature_tip->SetText(signature->GetText());
			signature_tip->SetVisible(true);
		}
	}
}
void CMainWindow::OnMenu(TNotifyUI& msg)
{

}
void CMainWindow::OnExit(TNotifyUI& msg)
{
	::SendMessage(m_hWnd,WM_SYSCOMMAND,SC_CLOSE,0);
}
LRESULT CMainWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	try
	{
		ModifyStyle(WS_CAPTION,WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		if(!RegisterSkin(_T("mainwindow.xml"),0,this))
			return 0;

		GetPaintMgr()->AddNotifier(this);
		RECT rcClient;
		::GetClientRect(*this, &rcClient);
		::SetWindowPos(*this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
			rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);

		CLogin* pLogin = new CLogin();
		pLogin->Create(m_hWnd,NULL,UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
		pLogin->CenterWindow();
		pLogin->BringWindowToTop();
		pLogin->ShowModal();
	}
	catch (...)
	{
		throw _T("CMainWindow::OnCreate");
	}
	return 0;
}
LRESULT CMainWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	try
	{
		// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
		if( wParam == SC_CLOSE ) {
			Sleep(1000);
			::PostQuitMessage(0L);
			bHandled = TRUE;
			return 0;
		}
		BOOL bZoomed = ::IsZoomed(*this);
		LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		if( ::IsZoomed(*this) != bZoomed ) {
			if( !bZoomed ) {
				CControlUI* pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(sysbtn::kMaxBtn));
				if( pControl ) pControl->SetVisible(false);
				pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(sysbtn::kRestoreBtn));
				if( pControl ) pControl->SetVisible(true);
			}
			else {
				CControlUI* pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(sysbtn::kMaxBtn));
				if( pControl ) pControl->SetVisible(true);
				pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(sysbtn::kRestoreBtn));
				if( pControl ) pControl->SetVisible(false);
			}
		}
		return lRes;
	}
	catch (...)
	{
		throw _T("CMainWindow::OnSysCommand");
	}
}
