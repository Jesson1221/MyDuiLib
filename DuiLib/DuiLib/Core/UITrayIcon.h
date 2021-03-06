#ifndef DuiTrayIcon_h__
#define DuiTrayIcon_h__

#ifdef _MSC_VER
#pragma once
#endif
#include <ShellAPI.h>

namespace DuiLib
{
	class UILIB_API CTrayIconUI : public IDuiObject
	{
	public:
		CTrayIconUI(void);
		~CTrayIconUI(void);
		virtual LPCTSTR GetClass() const;
		virtual bool    IsClass(LPCTSTR pstrClass);

	public:
		void CreateTrayIcon( HWND _RecvHwnd,UINT _IconIDResource,LPCTSTR _ToolTipText = NULL,UINT _Message = NULL/*(UIEVENT_TRAYICON)*/,CPaintManagerUI* pManager = NULL);
		void DeleteTrayIcon();
		bool SetTooltipText(LPCTSTR _ToolTipText);
		bool SetTooltipText(UINT _IDResource);
		CDuiString GetTooltipText() const;

		bool SetIcon(HICON _Hicon);
		bool SetIcon(LPCTSTR _IconFile);
		bool SetIcon(UINT _IDResource);
		HICON GetIcon() const;
		void SetHideIcon();
		void SetShowIcon();
		void RemoveIcon();
		bool StartTwinkling();
		void StopTwinkling();

		bool Enabled(){return m_bEnabled;};
		bool IsVisible(){return !m_bVisible;};
		bool IsTwinkling(){return m_bTwinkling;};
		bool IsMouseHover(){return m_bTrackMouse;};

		bool OnCommon(void* param);
		void OnTimer(IDuiTimer* pTimer, HWND hWnd, CTrayIconUI* lParam, WPARAM wParam);
		void OnTimerMousePt(IDuiTimer* pTimer, HWND hWnd, CTrayIconUI* lParam, WPARAM wParam);
	private:
		bool m_bEnabled;
		bool m_bVisible;
		bool m_bTwinkling;
		bool m_bTrackMouse;
		POINT m_ptMouse;
		HWND m_hWnd;
		UINT m_uMessage;
		HICON m_hIcon;
		IDuiTimer* pIDuiTimer;
		IDuiTimer* m_pDuiTime;
		NOTIFYICONDATA	m_trayData;
	};
}
#endif // DuiTrayIcon_h__

