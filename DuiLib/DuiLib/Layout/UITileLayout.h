#ifndef __UITILELAYOUT_H__
#define __UITILELAYOUT_H__

#ifdef _MSC_VER
#pragma once
#endif

namespace DuiLib
{
	class UILIB_API CTileLayoutUI : public CContainerUI
	{
	public:
		CTileLayoutUI();

		static LPCTSTR GetClassName();
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetPos(RECT rc);

		SIZE GetItemSize() const;
		void SetItemSize(SIZE szItem);
		int GetColumns() const;
		void SetColumns(int nCols);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		SIZE m_szItem;
		int m_nColumns;
	};
}
#endif // __UITILELAYOUT_H__
