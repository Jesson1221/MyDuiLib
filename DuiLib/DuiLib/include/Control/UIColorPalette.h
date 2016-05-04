/*********************************************************************
*  ����Ϊduilib�����Ķ�̬��ɫ��ؼ�����ȫģ�¿ṷ��QQ�ĵ�ɫ�幦��
*  ʹ����HSB����ģʽ��������Լ��о�����һ���㷨���ƽ���
*  �����ɫ����Դ���ģ�³��ṷ��ɫ�����ʽ�����ǻ��в��
*  �������λ����֪�����õ��㷨���������ƵĴ��룬���ߴ˴�����bug������ϵ��
*  By:Redrain  QQ��491646717   2014.8.19
*  Modify By Ц������ QQ: 89702120 2014-08-19 �ع�
*  ��������Ƶ����󣬿����޸������
*  sample:<ColorPalette name="Pallet" width="506" height="220" palletheight="200" barheight="14" padding="8,5,0,0" bkcolor="#FFFFFFFF" thumbimage="UI\skin\cursor.png" />
*
*  ��ģ��������ԭ���Ĵ����������ѡ���֮�������±�д�ģ��޸����㷨����������˶�̬��ɫ������ܣ�֮�����ֽ�����һ��bug���ٴθ�л��֮����Ĵ���
*********************************************************************/
#ifndef __UIColorPalette_H__
#define __UIColorPalette_H__

#pragma once

namespace DuiLib
{
	class	UILIB_API	CColorPaletteUI : public CControlUI
	{
	public:
		CColorPaletteUI();
		virtual ~CColorPaletteUI();

		static LPCTSTR GetClassName();
		LPCTSTR	GetClass() const;
		LPVOID	GetInterface(LPCTSTR pstrName);

		virtual	bool	Activate();
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		virtual void SetPos(RECT rc);
		virtual void DoInit();
		virtual void DoEvent(TEventUI& event);
		virtual void DoPaint(HDC hDC, const RECT& rcPaint);
		virtual void PaintPallet(HDC hDC);
	public:
		//��ȡ���ձ�ѡ�����ɫ������ֱ����������duilib����ɫ
		DWORD	GetSelectColor( bool bAlaph = true);
		void	SetSelectColor(DWORD dwColor);
		//����/��ȡ ��ɫ������͸��ֵ
		void	SetPaletteAlaph(int nAlaph);
		int		GetPaletteAlaph() const;

		//����/��ȡ Pallet����ɫ�������棩�ĸ߶�
		void	SetPalletHeight(int nHeight);
		int		GetPalletHeight() const;

		//����/��ȡ �·�Bar������ѡ�������ĸ߶�
		void	SetBarHeight(int nHeight);
		int		GetBarHeight() const;
		//����/��ȡ ѡ��ͼ���·��
		void	SetThumbImage(LPCTSTR pszImage);
		CDuiString	GetThumbImage() const;

	protected:
		//��������
		void	_UpdatePalletData();
		void	_UpdateBarData();

	protected:
		CDuiString	m_bmpImagePallet;
		MBmpImageCach	m_bmpImageBar;
		UINT		m_uButtonState;
		bool		m_bIsInBar;
		bool		m_bIsInPallet;
		int			m_nCurH;
		int			m_nCurS;
		int			m_nCurB;
	protected:
		int			m_nAlaph;
		int			m_nPalletHeight;
		int			m_nBarHeight;
		DuiLib::CPoint		m_ptLastPalletMouse;
		CDuiString		m_strThumbImage;
	};
};

#endif//__UIColorPalette_H__