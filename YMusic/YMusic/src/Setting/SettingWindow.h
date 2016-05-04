#pragma once



class CSettingWindow : 
	public YWindow ,
	public INotifyUI ,
	public IDialogBuilderCallback ,
	public Singleton<CSettingWindow>
{

public:
	CSettingWindow();
	~CSettingWindow();
	
protected:
	virtual void Notify(TNotifyUI& msg); 

	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//void OnPaint(CDCHandle dc);
	//void OnShowWindow(BOOL bShow, UINT nStatus);
	/*virtual*/ CControlUI* CreateControl(LPCTSTR pstrClass);
public:
	enum emTabPages
	{
		AboutPage,
		NormalPage,
		LrcPanelPage,
		LrcDeskPage,
		CachePage,
		HotKeyPage,
		UpdataPage,

		PageCount
	};

	enum emInsertModes
	{
		BeginPosMode,
		CurPosMode,
		EndPosMode
	};
	void showPage(emTabPages emPage);
private:
	struct
	{
		CFadeOptionUI *ConfigAbout_Option;//�������
		CFadeOptionUI *ConfigNormal_Option;//��������
		CFadeOptionUI *ConfigLrcPanel_Option;//�����ʾ
		CFadeOptionUI *ConfigLrcDesk_Option;//������
		CFadeOptionUI *ConfigCache_Option;//��������
		CFadeOptionUI *ConfigHotKey_Option;//�ȼ�����
		CFadeOptionUI *ConfigUpdate_Option;//�������
		//��������ҳ��
		CCheckBoxUI *AutoLogin_CheckBox;//�Զ���¼�˻�
		CCheckBoxUI *AutoPlay_CheckBox;//�Զ�����
		CCheckBoxUI *AutoRun_CheckBox;//��������
		CCheckBoxUI *AutoOpenLRC_CheckBox;//�Զ���ʾ������
		COptionUI *MinTrayIcon_Option;
		COptionUI *Exit_Option;

		CCheckBoxUI *PlayRoaming_CheckBox;//�����б����ɺ���������
		CCheckBoxUI *RelateFile_CheckBox;//�ļ�����
		//�����ʾ
		CButtonUI *ColorPicker_Btn1;
		CButtonUI *ColorPicker_Btn2;
		CButtonUI *ColorPicker_Btn3;
		CButtonUI *ColorPicker_Btn4;
		CButtonUI *ColorPicker_Btn5;
		CLabelUI *Color_Label1;
		CLabelUI *Color_Label2;
		CLabelUI *Color_Label3;
		CLabelUI *Color_Label4;
		CLabelUI *Color_Label5;
		CComboBoxUI *LrcPanelFontName;
		CComboBoxUI *LrcPanelFontStyle;
		CComboBoxUI *LrcPanelFontSize;
		CComboBoxUI *LrcDeskFontName;
		CComboBoxUI *LrcDeskFontStyle;
		CComboBoxUI *LrcDeskFontSize;
		CCheckBoxUI *LrcDeskKaraok;
		//������
		//��������ҳ��
		CEditUI *CacheDir_Edit;
		CEditUI *MaxCache_Edit;
		CLabelUI *CachedLabel;
		CButtonUI *ChangeDir_Btn;
		CButtonUI *OpenDir_Btn;
		CButtonUI *ClearCache_Btn;
		//�������
		CCheckBoxUI *AutoUpdate_CheckBox;

		//�ȼ�����ҳ��
		CAnimationTabLayoutUI *PanelItemTab_TabLayout;
		CButtonUI *CheckUpdate_Btn;
		CHotKeyUI *HK_Mode;
		CHotKeyUI *HK_Lrc;
		CHotKeyUI *HK_PlayPause;
		CHotKeyUI *HK_PreSong;
		CHotKeyUI *HK_NextSong;
		CHotKeyUI *HK_VolUp;
		CHotKeyUI *HK_VolDown;

		CButtonUI *Close_Btn;
		CButtonUI *Ok_Btn;
		CButtonUI *Cancle_Btn;
		CButtonUI *Apply_Btn;
	}ui;
	bool m_bModify;

	void init();
	void ok();
	void cancle();
	void apply();
	void setModify(bool isModify);
	void initUiStruct();
	void colorBox(CControlUI* pUI);
	DWORD dwFromText(LPCTSTR lpszValue);
	int   intFromText(LPCTSTR lpszValue,CComboBoxUI* pCombo);
};

