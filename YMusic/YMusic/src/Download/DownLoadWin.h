#ifndef __DOWNLOADWIN_H__
#define __DOWNLOADWIN_H__

#pragma once

#include "../../YMusic.h"

__MyNameSpaceBegin

/************************************************************************/
/* ���ع���������ģ��Ϊ����ģʽ                                         */
/************************************************************************/
class YDownLoadWin 
	: public YWindow
	, public INotifyUI
	, public IDialogBuilderCallback
	, public SkinChangedReceiver
	, public CNotifyPump
	, public Singleton<YDownLoadWin>
{
public:
	YDownLoadWin();
	virtual ~YDownLoadWin();

	static LPCTSTR GetWindowClass() ;
	LPCTSTR GetWindowClassName() const;
	void OnFinalMessage( HWND hWnd );
protected:
	virtual LRESULT OnCreate(UINT uMsg,LPARAM lparam,WPARAM wparam,BOOL& bHandled);

	virtual CControlUI*  CreateControl(LPCTSTR pstrClass);
	void         InitWindow();
	virtual BOOL Receive(SkinChangedParam param);
	virtual void Notify(TNotifyUI& msg);
private:
};


__MyNameSpaceEnd



#endif//__DOWNLOADWIN_H__