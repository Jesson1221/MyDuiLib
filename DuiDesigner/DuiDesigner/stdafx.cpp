// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// UIDesigner.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

CMainFrame* g_pMainFrame = NULL;
CToolBoxWnd* g_pToolBoxWnd = NULL;
CPropertiesWnd* g_pPropertiesWnd = NULL;
CFileView* g_pFileView = NULL;
CClassView* g_pClassView = NULL;
CResourceViewBar* g_pResourceView = NULL;
CHookAPI g_pHookAPI;

int gGetUIClass(LPCTSTR pstrClass)
{
	int nClass = classPointer;
	SIZE_T cchLen = _tcslen(pstrClass);
	switch( cchLen ) {
		case 6:
			if( _tcscmp(pstrClass, _T("FormUI")) == 0 )                   nClass=classWindow;
			else if( _tcscmp(pstrClass, _T("EditUI")) == 0 )              nClass=classEdit;
			else if( _tcscmp(pstrClass, _T("ListUI")) == 0 )              nClass=classList;
			else if( _tcscmp(pstrClass, _T("TextUI")) == 0 )              nClass=classText;
			break;
		case 7:
			if( _tcscmp(pstrClass, _T("ComboUI")) == 0 )                  nClass=classCombo;
			else if( _tcscmp(pstrClass, _T("LabelUI")) == 0 )             nClass=classLabel;
			else if (_tcscmp(pstrClass, _T("RadioUI")) == 0)             nClass = classRadio;
			else if (_tcscmp(pstrClass, _T("FlashUI")) == 0)             nClass = classFlash;
			break;
		case 8:
			if( _tcscmp(pstrClass, _T("ButtonUI")) == 0 )                 nClass=classButton;
			else if( _tcscmp(pstrClass, _T("OptionUI")) == 0 )            nClass=classOption;
			else if( _tcscmp(pstrClass, _T("SliderUI")) == 0 )            nClass=classSlider;
			break;
		case 9:
			if( _tcscmp(pstrClass, _T("ControlUI")) == 0 )                nClass=classControl;
			else if( _tcscmp(pstrClass, _T("ActiveXUI")) == 0 )           nClass=classActiveX;
			else if (_tcscmp(pstrClass, _T("GifAnimUI")) == 0)           nClass = classGifAnim;
			break;
		case 10:
			if( _tcscmp(pstrClass, _T("ProgressUI")) == 0 )               nClass=classProgress;
			else if (_tcscmp(pstrClass, _T("CheckBoxUI")) == 0)               nClass = classCheckBox;
			else if (_tcscmp(pstrClass, _T("ComboBoxUI")) == 0)               nClass = classComboBox;
			else if (_tcscmp(pstrClass, _T("DateTimeUI")) == 0)               nClass = classDateTime;
			else if (_tcscmp(pstrClass, _T("TreeViewUI")) == 0)               nClass = classTreeView;
			else if (_tcscmp(pstrClass, _T("RichEditUI")) == 0)               nClass = classRichEdit;
			break;
		case 11:
			if( _tcscmp(pstrClass, _T("ContainerUI")) == 0 )              nClass=classContainer;
			else if( _tcscmp(pstrClass, _T("TabLayoutUI")) == 0 )         nClass=classTabLayout;
			else if (_tcscmp(pstrClass, _T("WkeWebkitUI")) == 0)         nClass = classWkeBrowser;
			break;
		case 12:
			if( _tcscmp(pstrClass, _T("ListHeaderUI")) == 0 )             nClass=classListHeader;
			else if( _tcscmp(pstrClass, _T("TileLayoutUI")) == 0 )        nClass=classTileLayout;
			else if (_tcscmp(pstrClass, _T("VScrollBarUI")) == 0 )			nClass=classScrollBar;
			else if (_tcscmp(pstrClass, _T("HScrollBarUI")) == 0 )			nClass=classScrollBar;
			else if( _tcscmp(pstrClass, _T("WebBrowserUI")) == 0 )			nClass=classWebBrowser;
			else if (_tcscmp(pstrClass, _T("FadeButtonUI")) == 0)           nClass = classFadeButton;
			else if (_tcscmp(pstrClass, _T("FadeOptionUI")) == 0)           nClass = classFadeOption;
			break;
		case 13:
			if( _tcscmp(pstrClass, _T("ChildLayoutUI")) == 0 )             nClass=classChildLayout;
			break;
		case 14:
			if (_tcscmp(pstrClass, _T("FadeCheckBoxUI")) == 0)			  nClass = classFadeCheckBox;
			break;
		case 16:
			if( _tcscmp(pstrClass, _T("VerticalLayoutUI")) == 0 )         nClass=classVerticalLayout;
			else if( _tcscmp(pstrClass, _T("ListHeaderItemUI")) == 0 )    nClass=classListHeaderItem;
			break;
		case 17:
			if( _tcscmp(pstrClass, _T("ListTextElementUI")) == 0 )        nClass=classListTextElement;
			break;
		case 18:
			if( _tcscmp(pstrClass, _T("HorizontalLayoutUI")) == 0 )       nClass=classHorizontalLayout;
			else if( _tcscmp(pstrClass, _T("ListLabelElementUI")) == 0 )  nClass=classListLabelElement;
			break;
		case 20:
			if (_tcscmp(pstrClass, _T("AnimationTabLayoutUI")) == 0)       nClass = classAnimTabLayout;
			break;
		case 22:
			if( _tcscmp(pstrClass, _T("ListContainerElementUI")) == 0 )   nClass=classListContainerElement;
			break;
	}

	return nClass;
}
int gGetUIClass(CControlUI* pControl)
{
	if(pControl==NULL)
		return classPointer;

	return gGetUIClass(pControl->GetClass());
}