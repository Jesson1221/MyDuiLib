#include "UIlib.h"
#include "UIReflection.h"

namespace DuiLib
{

	//************************************
	// ��������: RegistDuiClass
	// ��������: void
	// ������Ϣ: string _duiClassName					����
	// ������Ϣ: DuiInstanceFun _createDuiInstanceFun	ע��ĺ���ָ��
	// ����˵�����෴��ע�ᣬ���Ѿ�ע�������ֱ�ӷ���
	//************************************
	void DuiObjectMap::RegisterDuiClass(LPCTSTR _duiClassName, DuiInstanceFun _createDuiInstanceFun)
	{
		if (GetDuiClassMaps().size() > 0 && GetDuiClassMaps().find(_duiClassName) != GetDuiClassMaps().end())
			return;

		GetDuiClassMaps()[_duiClassName] = _createDuiInstanceFun;
		DUITRACE(_T("RegisterDuiClass:Ԥע��UI�齨%s\r\n"), _duiClassName);
	}
	void* DuiObjectMap::createInstance(LPCTSTR _duiClassName)
	{
		if (GetDuiClassMaps().size() > 0 && GetDuiClassMaps().find(_duiClassName) == GetDuiClassMaps().end())
		{
			std::map<CDuiString, DuiInstanceFun>& mDuiClassMaps = GetDuiClassMaps();
			LPCTSTR str = _T("û���ҵ������%s ,�ö����಻����DuiLib��ע���,�����ⲿ����CreateControl\r\n");
			DUITRACE(str, _duiClassName);
			DuiLogWarning(str, _duiClassName);
			return NULL;
		}
		else
		{
			return (GetDuiClassMaps()[_duiClassName])();
		}
	}
	std::map<CDuiString, DuiInstanceFun>& DuiObjectMap::GetDuiClassMaps()
	{
		static std::map<CDuiString, DuiInstanceFun> m_duiClassMaps;
		return m_duiClassMaps;
	}
	bool DuiObjectMap::isRegister(LPCTSTR _duiClassName)
	{
		if (GetDuiClassMaps().size() == 0 || GetDuiClassMaps().find(_duiClassName) == GetDuiClassMaps().end())
		{
			return false;
		}
		return true;
	}
}

