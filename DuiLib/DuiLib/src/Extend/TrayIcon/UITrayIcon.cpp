#include "StdAfx.h"
#include "UITrayIcon.h"

namespace DuiLib
{

	CTrayIconUI::CTrayIconUI(void)
	{
		memset(&m_trayData, 0, sizeof(m_trayData));
		m_bEnabled		= false;
		m_bVisible		= false;
		m_bTwinkling	= false;
		m_bTrackMouse	= false;
		m_pDuiTime		= NULL;
		m_hWnd			= NULL;
		pIDuiTimer		= NULL;
		m_uMessage		= UIEVENT_TRAYICON;
	}


	CTrayIconUI::~CTrayIconUI(void)
	{
		DeleteTrayIcon();
	}

	//************************************
	// ��������: CreateTrayIcon
	// ��������: void
	// ������Ϣ: HWND _RecvHwnd
	// ������Ϣ: LPCTSTR _ToolTipText
	// ������Ϣ: UINT _Message
	// ������Ϣ: HICON _DefaultIcon
	// ����˵��: 
	//************************************
	void CTrayIconUI::CreateTrayIcon( HWND _RecvHwnd,UINT _IconIDResource,LPCTSTR _ToolTipText /*= NULL*/,UINT _Message /*= UIEVENT_TRAYICON*/,CPaintManagerUI* pManager/* = NULL*/)
	{
		if(_Message == NULL)
			_Message = UIEVENT_TRAYICON;

		if(!_RecvHwnd || _IconIDResource <= 0 || _Message < 0)
			return;

		m_hIcon = LoadIcon(CPaintManagerUI::GetInstance(),MAKEINTRESOURCE(_IconIDResource));

		m_trayData.cbSize = sizeof(NOTIFYICONDATA);
		m_trayData.hWnd	 = _RecvHwnd;
		m_trayData.uID	 = _IconIDResource;
		m_trayData.hIcon = m_hIcon;
		m_trayData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		m_trayData.uCallbackMessage = _Message;
		if(_ToolTipText)
			lstrcpyn(m_trayData.szTip, _ToolTipText, 63);

		Shell_NotifyIcon(NIM_ADD,&m_trayData);
		m_bEnabled = true;

		m_pDuiTime = MakeDuiTimer(this,&CTrayIconUI::OnTimerMousePt,_RecvHwnd,this,NULL,200);
		m_pDuiTime->SetDuiTimer();

		//if(pManager)
		//	pManager->GetEventSource() += MakeDelegate(this,&CTrayIconUI::OnCommon,UIEVENT_TRAYICON);
	}
	
	//************************************
	// ��������: DeleteTrayIcon
	// ��������: void
	// ����˵��: 
	//************************************
	void CTrayIconUI::DeleteTrayIcon()
	{
		if(pIDuiTimer)
			StopTwinkling();

		if(m_pDuiTime){
			m_pDuiTime->KillDuiTimer();
			delete m_pDuiTime;
			m_pDuiTime = NULL;
		}
				
		Shell_NotifyIcon(NIM_DELETE,&m_trayData);
		m_bEnabled		= false;
		m_bVisible		= false;
		m_bTwinkling	= false;
		m_hWnd			= NULL;
		m_uMessage		= UIEVENT_TRAYICON;
	}

	//************************************
	// ��������: SetTooltipText
	// ��������: bool
	// ������Ϣ: LPCTSTR _ToolTipText
	// ����˵��: 
	//************************************
	bool CTrayIconUI::SetTooltipText( LPCTSTR _ToolTipText )
	{
		if(_ToolTipText)
			lstrcpyn(m_trayData.szTip, _ToolTipText, 63);


		if (!m_bEnabled) return FALSE;
		m_trayData.uFlags = NIF_TIP;
		return Shell_NotifyIcon(NIM_MODIFY, &m_trayData) == TRUE;
	}

	//************************************
	// ��������: SetTooltipText
	// ��������: bool
	// ������Ϣ: UINT _IDResource
	// ����˵��: 
	//************************************
	bool CTrayIconUI::SetTooltipText( UINT _IDResource )
	{
#ifdef UNICODE
		wchar_t mbuf[64];
		LoadString(CPaintManagerUI::GetInstance(),_IDResource,mbuf,64);

		return SetTooltipText(mbuf);
#else
		char mbuf[64];
		LoadString(CPaintManagerUI::GetInstance(), _IDResource, mbuf, 64);

		return SetTooltipText(mbuf);
#endif
	}

	//************************************
	// ��������: GetTooltipText
	// ��������: UiLib::CDuiString
	// ����˵��: 
	//************************************
	CDuiString CTrayIconUI::GetTooltipText() const
	{
		return m_trayData.szTip;
	}

	//************************************
	// ��������: SetIcon
	// ��������: bool
	// ������Ϣ: HICON _Hicon
	// ����˵��: 
	//************************************
	bool CTrayIconUI::SetIcon( HICON _Hicon )
	{
		if(_Hicon)
			m_hIcon = _Hicon;

		m_trayData.uFlags = NIF_ICON;
		m_trayData.hIcon = _Hicon;
		
		if (!m_bEnabled) return FALSE;
		return Shell_NotifyIcon(NIM_MODIFY, &m_trayData) == TRUE;

		return false;
	}

	//************************************
	// ��������: SetIcon
	// ��������: bool
	// ������Ϣ: LPCTSTR _IconFile
	// ����˵��: 
	//************************************
	bool CTrayIconUI::SetIcon( LPCTSTR _IconFile )
	{
		HICON hIcon = LoadIcon(CPaintManagerUI::GetInstance(),_IconFile);
		return SetIcon(hIcon);
	}

	//************************************
	// ��������: SetIcon
	// ��������: bool
	// ������Ϣ: UINT _IDResource
	// ����˵��: 
	//************************************
	bool CTrayIconUI::SetIcon( UINT _IDResource )
	{
		HICON hIcon = LoadIcon(CPaintManagerUI::GetInstance(),MAKEINTRESOURCE(_IDResource));
		return SetIcon(hIcon);
	}

	//************************************
	// ��������: GetIcon
	// ��������: HICON
	// ����˵��: 
	//************************************
	HICON CTrayIconUI::GetIcon() const
	{
		HICON hIcon = NULL;
		hIcon = m_trayData.hIcon;
		return hIcon;
	}

	//************************************
	// ��������: SetHideIcon
	// ��������: void
	// ����˵��: 
	//************************************
	void CTrayIconUI::SetHideIcon()
	{
		if (IsVisible()) {
			SetIcon((HICON)NULL);
			m_bVisible = TRUE;
		}
	}

	//************************************
	// ��������: SetShowIcon
	// ��������: void
	// ����˵��: 
	//************************************
	void CTrayIconUI::SetShowIcon()
	{
		if (!IsVisible()) {
			SetIcon(m_hIcon);
			m_bVisible = FALSE;
		}
	}

	//************************************
	// ��������: RemoveIcon
	// ��������: void
	// ����˵��: 
	//************************************
	void CTrayIconUI::RemoveIcon()
	{
		m_trayData.uFlags = 0;
		Shell_NotifyIcon(NIM_DELETE, &m_trayData);
		m_bEnabled = FALSE;
	}

	//************************************
	// ��������: StartTwinkling
	// ��������: bool
	// ����˵��: 
	//************************************
	bool CTrayIconUI::StartTwinkling()
	{
		if(m_bTwinkling || !m_bEnabled || pIDuiTimer)
			return false;

		pIDuiTimer = MakeDuiTimer(this,&CTrayIconUI::OnTimer,m_hWnd,this,NULL,400);
		pIDuiTimer->SetDuiTimer();
		m_bTwinkling = true;
		return true;
	}

	//************************************
	// ��������: StopTwinkling
	// ��������: void
	// ����˵��: 
	//************************************
	void CTrayIconUI::StopTwinkling()
	{
		if(pIDuiTimer){
			pIDuiTimer->KillDuiTimer();
			delete pIDuiTimer;
			pIDuiTimer = NULL;
		}
		m_bTwinkling = false;
		SetShowIcon();
	}
	
	//************************************
	// ��������: OnCommon
	// ��������: bool
	// ������Ϣ: TEventUI * pTEventUI
	// ������Ϣ: LPARAM lParam
	// ������Ϣ: WPARAM wParam
	// ����˵��: 
	//************************************
	bool CTrayIconUI::OnCommon( TEventUI* pTEventUI,LPARAM lParam,WPARAM wParam )
	{
		if(m_trayData.uID == pTEventUI->wParam && pTEventUI->lParam == WM_MOUSEMOVE)
		{
			GetCursorPos(&m_ptMouse);
			if(!m_bTrackMouse)
			{
				m_bTrackMouse = true;
				PostMessage(m_hWnd,WM_MOUSEINTRAYICON,NULL,NULL);
			}
		}
		return true;
	}

	//************************************
	// ��������: OnTimer
	// ��������: void
	// ������Ϣ: IDuiTimer * pTimer
	// ������Ϣ: HWND hWnd
	// ������Ϣ: CTrayIconUI * lParam
	// ������Ϣ: WPARAM wParam
	// ����˵��: 
	//************************************
	void CTrayIconUI::OnTimer( IDuiTimer* pTimer,HWND hWnd,CTrayIconUI* lParam,WPARAM wParam )
	{
		IsVisible()?SetHideIcon():SetShowIcon();
	}

	//************************************
	// ��������: OnTimerMousePt
	// ��������: void
	// ������Ϣ: IDuiTimer * pTimer
	// ������Ϣ: HWND hWnd
	// ������Ϣ: CTrayIconUI * lParam
	// ������Ϣ: WPARAM wParam
	// ����˵��: 
	//************************************
	void CTrayIconUI::OnTimerMousePt( IDuiTimer* pTimer,HWND hWnd,CTrayIconUI* lParam,WPARAM wParam )
	{
		if(m_bTrackMouse)
		{
			POINT ptMouse;
			GetCursorPos(&ptMouse);
			if(ptMouse.x != m_ptMouse.x || ptMouse.y != m_ptMouse.y)
			{
				m_bTrackMouse = false;
				PostMessage(hWnd,WM_MOUSEOUTTRAYICON,NULL,NULL);
			}
		}
	}
}
