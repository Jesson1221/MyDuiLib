#ifndef __UIDLGBUILDER_H__
#define __UIDLGBUILDER_H__

#ifdef _MSC_VER
#pragma once
#endif

namespace DuiLib {

class IDialogBuilderCallback
{
public:
	virtual CControlUI* CreateControl(LPCTSTR pstrClass) = 0;
};

class UILIB_API IDialogBuilderCustomHandle : public IDialogBuilderCallback
{
public:	
	virtual CControlUI* CreateFromXML(STRINGorID xml, LPCTSTR type = NULL, CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);
private:
	virtual CControlUI* CreateFromXML(CMarkup* pXML, LPCTSTR type = NULL, CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);

private:
	CControlUI* _Parse(CMarkupNode* pRoot, LPCTSTR type = NULL, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL);
};


class UILIB_API CDialogBuilder : public IDuiObject
{
public:
	virtual bool IsClass(LPCTSTR pstrClass);
	virtual LPCTSTR GetClass() const;
	static LPCTSTR GetClassName();

    CDialogBuilder();
    CControlUI* Create(STRINGorID xml, LPCTSTR type = NULL, IDialogBuilderCallback* pCallback = NULL,
        CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);
    CControlUI* Create(IDialogBuilderCallback* pCallback = NULL, CPaintManagerUI* pManager = NULL,
        CControlUI* pParent = NULL);

    CMarkup* GetMarkup();

    void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
    void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;
private:
	CControlUI* _Parse(CMarkupNode* pRoot, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL);

    CMarkup m_xml;
    IDialogBuilderCallback* m_pCallback;
    LPCTSTR m_pstrtype;
};

} // namespace DuiLib

#endif // __UIDLGBUILDER_H__
