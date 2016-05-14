#ifndef __UICOMBOBOX_H__
#define __UICOMBOBOX_H__

#ifdef _MSC_VER
#pragma once
#endif

namespace DuiLib
{
	/// ��չ�����б��
	/// ����arrowimage����,һ��ͼƬƽ���ֳ�5��,Normal/Hot/Pushed/Focused/Disabled(������source����)
	/// <Default name="ComboBox" value="arrowimage=&quot;file='sys_combo_btn.png' source='0,0,16,16'&quot; "/>
	class UILIB_API CComboBoxUI : public CComboUI
	{
	public:
		CComboBoxUI();


		// add by rz.li
		static LPCTSTR GetClassName();

		LPCTSTR GetClass() const;

		LPCTSTR GetArrowImage() const;
		void SetArrowImage(LPCTSTR pStrImage);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintText(HDC hDC);
		void PaintStatusImage(HDC hDC);

	protected:
		CDuiString m_sArrowImage;
		int        m_nArrowWidth;
	};
}

#endif // __UICOMBOBOX_H__
