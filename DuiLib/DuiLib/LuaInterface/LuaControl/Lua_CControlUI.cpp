#include "LuaEntry.h"

#include REQUIRE_H(CControlUI)

namespace DuiLib
{

	LUA_METHOD_IMPL(CControlUI, isnil)
	{
		CControlUI* self;
		self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

		lua_pushboolean(l, self == NULL);
		return 1;
	}

	LUA_METHOD_IMPL(CControlUI, New)
	{
		CControlUI  *ctrl = new CControlUI();
		LuaStatic::AddObject2Lua(l,ctrl, MetaName());
		return 1;
	}

	LUA_METHOD_IMPL(CControlUI, Delete)
	{
		CControlUI* self;
		self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

		LuaStatic::RemoveObjectInLua(l);

		SafeDelete(self);

		return 0;
	}

	LUA_METHOD_IMPL(CControlUI, _gc)
	{	
		CControlUI* self;
		self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

		LuaStatic::RemoveObjectInLua(l);

		SafeDelete(self);

		return 0;
	}

	LUA_METHOD_IMPL(CControlUI, _eq)
	{
		try
		{
			CControlUI* left;
			left = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CControlUI* right;
			right = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));

			if (left == right) {
				lua_pushboolean(l, 1);
			}
			else {
				lua_pushboolean(l, 0);
			}

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::_eq"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, _tostring)
	{
		try
		{
			CControlUI* self;
			self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			if (self)
			{
				CDuiString str = CDuiString::FormatString(_T("%s(addr:%p,name:%s)"), self->GetClass(), (void*)self, self->GetName().GetData());
				lua_pushstring(l, str.GetAString().c_str());
			}
			else
			{
				CDuiString str = CDuiString::FormatString(_T("%s(addr:%s)"), "CControlUI", "nil");
				lua_pushstring(l, str.GetAString().c_str());
			}

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::_tostring"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsClass)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			if (ctrl)
			{
				lua_pushboolean(l, ctrl->IsClass(pstrText.GetData()) ? 1 : 0);
			}
			else
			{
				lua_pushboolean(l, 0);
			}

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsClass"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsName)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			if (ctrl)
			{
				lua_pushboolean(l, ctrl->IsName(pstrText.GetData()) ? 1 : 0);
			}
			else
			{
				lua_pushboolean(l, 0);
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsName"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetClassName)
	{
		CDuiString pstrText = CControlUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CControlUI, GetName)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			if (ctrl)
			{
				CDuiString pstrText = ctrl->GetName();

				lua_op_t<CDuiString>::push_stack(l, pstrText);
			}
			else
			{
				lua_pushnil(l);
			}

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetName"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetName)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
		
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			if (ctrl)
			{
				ctrl->SetName(pstrText.GetData());
			}

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetName"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetClass)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			if (ctrl)
			{
				CDuiString pstrText = ctrl->GetClass();

				lua_op_t<CDuiString>::push_stack(l, pstrText);
			}
			else
			{
				lua_pushnil(l);
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetClass"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetInterface)
	{
		try
		{
			CControlUI* self;
			self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			LPVOID pInter = self->GetInterface(pstrText.GetData());

			if (pInter)
			{
				CControlUI* pControl = static_cast<CControlUI*>(pInter);
				LuaStatic::AddObject2Lua(l, pControl, METATABLE_NAME(pControl));
			}
			else
				lua_pushnil(l);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetInterface"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetControlFlags)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			
			if (ctrl)
			{
				UINT   flags;
				flags = ctrl->GetControlFlags();

				lua_pushinteger(l, (lua_Integer)flags);
			}
			else
			{
				lua_pushnil(l);
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetControlFlags"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, Activate)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			if (ctrl)
			{
				lua_pushboolean(l, ctrl->Activate() ? 1 : 0);
			}
			else
			{
				lua_pushboolean(l, 0);
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::Activate"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetManager)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			if (ctrl && ctrl->GetManager())
			{
				LuaStatic::AddObject2Lua(l, ctrl->GetManager(), METATABLE_NAME(ctrl));
			}
			else
			{
				lua_pushnil(l);
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetManager"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetManager)
	{
		try
		{
			CControlUI* self;
			self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CPaintManagerUI* pm;
			pm = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 2));

			CControlUI* parent;
			parent = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 3));

			bool       bInit = true;
			if (!lua_isnil(l,4))
				bInit = lua_toboolean(l, 4) != 0;

			self->SetManager(pm, parent, bInit);
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetManager"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetParent)
	{
		try
		{
			CControlUI* self;
			self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			if (self && self->GetParent())
			{
				LuaStatic::AddObject2Lua(l, self->GetParent(),METATABLE_NAME(self->GetParent()));
			}
			else
			{
				lua_pushnil(l);
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetParent"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, SetCustomStyle)
	{
		try
		{
			CControlUI* self;
			self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

		
			self->SetCustomStyle(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetCustomStyle"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetCustomStyle2)
	{
		try
		{
			CControlUI* self;
			self = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			
			CStdStringPtrMap* pMap = NULL;
			pMap = static_cast<CStdStringPtrMap*>(LuaStatic::CheckUserData(l, 2));

			self->SetCustomStyle2(pMap);

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetCustomStyle2"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetText)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = ctrl->GetText();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetText"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetText)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
		
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			ctrl->SetText(pstrText.GetData());

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetText"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetBkColor)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			
			DWORD dwBkCor = ctrl->GetBkColor();
			
			LuaStatic::WriteRGBA2Lua(l, dwBkCor);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBkColor)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			ctrl->SetBkColor(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBkColor"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CControlUI, GetBkColor2)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = ctrl->GetBkColor2();

			LuaStatic::WriteRGBA2Lua(l, dwBkCor);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBkColor2"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBkColor2)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			ctrl->SetBkColor2(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBkColor2"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CControlUI, GetBkColor3)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = ctrl->GetBkColor3();
			LuaStatic::WriteRGBA2Lua(l, dwBkCor);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBkColor3"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBkColor3)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			ctrl->SetBkColor3(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBkColor3"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CControlUI, GetBkImage)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = ctrl->GetBkImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBkImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBkImage)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			ctrl->SetBkImage(pstrText.GetData());

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBkImage"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetFocusBorderColor)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = ctrl->GetFocusBorderColor();

			LuaStatic::WriteRGBA2Lua(l, dwBkCor);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetFocusBorderColor"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, SetFocusBorderColor)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			ctrl->SetFocusBorderColor(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetFocusBorderColor"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CControlUI, IsColorHSL)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			bool isHSL = ctrl->IsColorHSL();

			lua_pushboolean(l, isHSL ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsColorHSL"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetColorHSL)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int isHSL = lua_toboolean(l, 2);

			ctrl->SetColorHSL(isHSL != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetColorHSL"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetBorderRound)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			SIZE rd = ctrl->GetBorderRound();

			LuaStatic::WriteSize2Lua(l, rd);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBorderRound"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBorderRound)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			SIZE rd = LuaStatic::ReadSizeFromLua(l, 2);
			ctrl->SetBorderRound(rd);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBorderRound"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetBorderSize();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBorderSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetBorderSize(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBorderSize"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetBorderColor)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = ctrl->GetBorderColor();

			LuaStatic::WriteRGBA2Lua(l, dwBkCor);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBorderColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBorderColor)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			ctrl->SetBorderColor(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBorderColor"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, SetBorderRect)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			RECT rd = LuaStatic::ReadRectFromLua(l, 2);
			
			ctrl->SetBorderSize(rd);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBorderRect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetLeftBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetLeftBorderSize();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetLeftBorderSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetLeftBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetLeftBorderSize(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetLeftBorderSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetTopBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetTopBorderSize();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetTopBorderSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetTopBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetTopBorderSize(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetTopBorderSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetRightBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetRightBorderSize();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetRightBorderSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetRightBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetRightBorderSize(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetRightBorderSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetBottomBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetBottomBorderSize();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBottomBorderSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBottomBorderSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetBottomBorderSize(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBottomBorderSize"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetBorderStyle)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetBorderStyle();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetBorderStyle"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetBorderStyle)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetBorderStyle(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetBorderStyle"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetPos)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			RECT rt = ctrl->GetPos();

			LuaStatic::WriteRect2Lua(l, rt);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetPos"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetPos)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			RECT rt = LuaStatic::ReadRectFromLua(l, 2);
			ctrl->SetPos(rt);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetPos"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetWidth();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetHeight)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetHeight();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetHeight"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetX)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetX();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetX"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetY)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetY();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetY"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetPadding)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			RECT rt = ctrl->GetPadding();

			LuaStatic::WriteRect2Lua(l, rt);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetPadding"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetPadding)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			RECT rt = LuaStatic::ReadRectFromLua(l, 2);
			ctrl->SetPadding(rt);
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetPadding"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetFixedXY)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			SIZE size = ctrl->GetFixedXY();

			//
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetFixedXY"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetFixedXY)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			//
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetFixedXY"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetFixedWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetFixedWidth();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetFixedWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetFixedWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetFixedWidth(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetFixedWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetFixedHeight)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetFixedHeight();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetFixedHeight"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetFixedHeight)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetFixedWidth(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetFixedHeight"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetMinWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetMinWidth();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetMinWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetMinWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetMinWidth(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetMinWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetMaxWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetMaxWidth();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetMaxWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetMaxWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetMaxWidth(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetMaxWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetMinHeight)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetMinHeight();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetMinHeight"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetMinHeight)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetMinHeight(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetMinHeight"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetMaxHeight)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetMaxHeight();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetMaxHeight"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetMaxHeight)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetMaxHeight(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetMaxHeight"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, SetRelativePos)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			SIZE move = LuaStatic::ReadSizeFromLua(l, 2);
			SIZE zoom = LuaStatic::ReadSizeFromLua(l, 3);

			ctrl->SetRelativePos(move,zoom);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetRelativePos"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetRelativeParentSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			SIZE sz = LuaStatic::ReadSizeFromLua(l, 2);

			ctrl->SetRelativeParentSize(sz);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetRelativeParentSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetRelativePos)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			//int size = ctrl->GetRelativePos();

			//lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetRelativePos"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, IsRelativePos)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsRelativePos() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsRelativePos"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetSoundNameOver)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText = ctrl->GetSoundNameOver();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetSoundNameOver"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetSoundNameOver)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			ctrl->SetSoundNameOver(pstrText.GetData());

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetSoundNameOver"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetSoundNameDown)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText = ctrl->GetSoundNameDown();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetSoundNameDown"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetSoundNameDown)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			ctrl->SetSoundNameDown(pstrText.GetData());

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetSoundNameDown"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetStyleName)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText = ctrl->GetStyleName();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetStyleName"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetStyleName)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			
			ctrl->SetStyleName(pstrText.GetData());

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetStyleName"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetToolTip)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText = ctrl->GetToolTip();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetToolTip"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetToolTip)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			ctrl->SetToolTip(pstrText.GetData());

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetToolTip"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, GetToolTipWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetToolTipWidth();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetToolTipWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetToolTipWidth)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetToolTipWidth(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetToolTipWidth"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetShortcut)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = ctrl->GetShortcut();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetShortcut"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetShortcut)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			ctrl->SetShortcut(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetShortcut"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsContextMenuUsed)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsContextMenuUsed() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsContextMenuUsed"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetContextMenuUsed)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			bool m = lua_toboolean(l, 2) != 0;

			ctrl->SetContextMenuUsed(m);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetContextMenuUsed"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetUserData)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString sName = ctrl->GetUserData();
			lua_pushstring(l, sName.GetAString().c_str());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetUserData"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetUserData)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			ctrl->SetUserData(pstrText.GetData());

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetUserData"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetTag)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushinteger(l, (int)ctrl->GetTag());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetTag"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetTag)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			ctrl->SetTag(lua_tointeger(l,2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetTag"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetTagCtrl)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* tagCtrl;
			tagCtrl = ctrl->GetTagCtrl();
			if (tagCtrl)
			{
				LuaStatic::AddObject2Lua(l, tagCtrl,METATABLE_NAME(tagCtrl));
			}
			else
				lua_pushnil(l);
			
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetTagCtrl"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetTagCtrl)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* tagCtrl;
			tagCtrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));

			ctrl->SetTagCtrl(tagCtrl);

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetTagCtrl"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsVisible)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsVisible() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsVisible"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetVisible)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			ctrl->SetVisible(0 != lua_toboolean(l, 2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetVisible"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetInternVisible)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			ctrl->SetInternVisible(0 != lua_toboolean(l, 2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetInternVisible"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsEnabled)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsEnabled() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsEnabled"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetEnabled)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			ctrl->SetEnabled(0 != lua_toboolean(l, 2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetEnabled"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsMouseEnabled)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsMouseEnabled() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsMouseEnabled"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetMouseEnabled)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			ctrl->SetMouseEnabled(0 != lua_toboolean(l, 2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetMouseEnabled"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsKeyboardEnabled)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsKeyboardEnabled() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsKeyboardEnabled"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetKeyboardEnabled)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			ctrl->SetKeyboardEnabled(0 != lua_toboolean(l, 2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetKeyboardEnabled"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsFocused)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsFocused() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsFocused"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetFocus)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			ctrl->SetFocus();

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetFocus"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, IsFloat)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsFloat() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsFloat"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, SetFloat)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			if (lua_isnone(l, 2))
				ctrl->SetFloat(true);
			else
				ctrl->SetFloat(0 != lua_toboolean(l, 2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetFloat"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, Invalidate)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			ctrl->Invalidate();

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::Invalidate"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, IsUpdateNeeded)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, ctrl->IsUpdateNeeded() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::IsUpdateNeeded"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, NeedUpdate)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			ctrl->NeedUpdate();

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::NeedUpdate"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, NeedParentUpdate)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			ctrl->NeedParentUpdate();

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::NeedParentUpdate"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, GetAdjustColor)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCol = LuaStatic::ReadRGBAFromLua(l, 2);

			DWORD dwBkCor = ctrl->GetAdjustColor(dwCol);

			LuaStatic::WriteRGBA2Lua(l, dwBkCor);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetAdjustColor"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, SetAttribute)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));
			
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			CDuiString pstrText2;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText2);


			ctrl->SetAttribute(pstrText, pstrText2);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetAttribute"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CControlUI, ApplyAttributeList)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			ctrl->ApplyAttributeList(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::ApplyAttributeList"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, EstimateSize)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			SIZE szAva = LuaStatic::ReadSizeFromLua(l, 2);

			SIZE st = ctrl->EstimateSize(szAva);
			LuaStatic::WriteSize2Lua(l, st);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::EstimateSize"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CControlUI, GetVirtualWnd)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText = ctrl->GetVirtualWnd();

			lua_op_t<CDuiString>::push_stack(l, pstrText);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::GetVirtualWnd"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CControlUI, SetVirtualWnd)
	{
		try
		{
			CControlUI* ctrl;
			ctrl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 1));

			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			ctrl->SetVirtualWnd(pstrText.GetData());

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCControlUI::SetVirtualWnd"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CControlUI)
	{
		lua_newtable(l); // t,

		static LuaReg StaticFuncs[] =
		{
			{ "GetClassName", GetClassName },
			{ "New", New },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs,sizeof(StaticFuncs)/sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, ExportName());
		
		luaL_newmetatable(l, MetaName());
			
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");

		static LuaReg MethodFuncs[] =
		{
			{ "isnil",isnil },
			{ "__eq",_eq },
			{ "__gc",_gc },
			{ "__tostring", _tostring },
			{ "IsClass", IsClass },
			{ "IsName", IsName },
			{ "GetName", GetName },
			{ "SetName", SetName },
			{ "Delete", Delete },
			{ "GetClass", GetClass },
			{ "GetInterface", GetInterface },
			{ "GetControlFlags", GetControlFlags },
			{ "Activate", Activate },
			{ "GetManager", GetManager },
			{ "SetManager", SetManager },
			{ "GetParent", GetParent },
			{ "SetCustomStyle", SetCustomStyle },
			{ "SetCustomStyle2", SetCustomStyle2 },
			{ "GetText", GetText },
			{ "SetText", SetText },
			{ "GetBkColor", GetBkColor },
			{ "SetBkColor", SetBkColor },
			{ "GetBkColor2", GetBkColor2 },
			{ "SetBkColor2", SetBkColor2 },
			{ "GetBkColor3", GetBkColor3 },
			{ "SetBkColor3", SetBkColor3 },
			{ "GetBkImage", GetBkImage },
			{ "SetBkImage", SetBkImage },
			{ "GetFocusBorderColor", GetFocusBorderColor },
			{ "SetFocusBorderColor", SetFocusBorderColor },
			{ "IsColorHSL", IsColorHSL },
			{ "SetColorHSL", SetColorHSL },
			{ "GetBorderRound", GetBorderRound },
			{ "SetBorderRound", SetBorderRound },
			//{ "DrawImage", DrawImage },
			{ "GetBorderSize", GetBorderSize },
			{ "SetBorderSize", SetBorderSize },
			{ "GetBorderColor", GetBorderColor },
			{ "SetBorderColor", SetBorderColor },
			{ "SetBorderRect", SetBorderRect },
			{ "GetLeftBorderSize", GetLeftBorderSize },
			{ "SetLeftBorderSize", SetLeftBorderSize },
			{ "GetTopBorderSize", GetTopBorderSize },
			{ "SetTopBorderSize", SetTopBorderSize },
			{ "GetRightBorderSize", GetRightBorderSize },
			{ "SetRightBorderSize", SetRightBorderSize },
			{ "GetBottomBorderSize", GetBottomBorderSize },
			{ "SetBottomBorderSize", SetBottomBorderSize },
			{ "GetBorderStyle", GetBorderStyle },
			{ "SetBorderStyle", SetBorderStyle },
			{ "GetPos", GetPos },
			{ "SetPos", SetPos },
			{ "GetWidth", GetWidth },
			{ "GetHeight", GetHeight },
			{ "GetX", GetX },
			{ "GetY", GetY },
			{ "GetPadding", GetPadding },
			{ "SetPadding", SetPadding },
			{ "GetFixedXY", GetFixedXY },
			{ "SetFixedXY", SetFixedXY },
			{ "GetFixedWidth", GetFixedWidth },
			{ "SetFixedWidth", SetFixedWidth },
			{ "GetFixedHeight", GetFixedHeight },
			{ "SetFixedHeight", SetFixedHeight },
			{ "GetMinWidth", GetMinWidth },
			{ "SetMinWidth", SetMinWidth },
			{ "GetMaxWidth", GetMaxWidth },
			{ "SetMaxWidth", SetMaxWidth },
			{ "GetMinHeight", GetMinHeight },
			{ "SetMinHeight", SetMinHeight },
			{ "GetMaxHeight", GetMaxHeight },
			{ "SetMaxHeight", SetMaxHeight },
			{ "SetRelativePos", SetRelativePos },
			{ "SetRelativeParentSize", SetRelativeParentSize },
			{ "GetRelativePos", GetRelativePos },
			{ "IsRelativePos", IsRelativePos },
			{ "GetSoundNameOver", GetSoundNameOver },
			{ "SetSoundNameOver", SetSoundNameOver },
			{ "GetSoundNameDown", GetSoundNameDown },
			{ "SetSoundNameDown", SetSoundNameDown },
			{ "GetStyleName", GetStyleName },
			{ "SetStyleName", SetStyleName },
			{ "GetToolTip", GetToolTip },
			{ "SetToolTip", SetToolTip },
			{ "SetToolTipWidth", SetToolTipWidth },
			{ "GetToolTipWidth", GetToolTipWidth },
			{ "GetShortcut", GetShortcut },
			{ "SetShortcut", SetShortcut },
			{ "IsContextMenuUsed", IsContextMenuUsed },
			{ "SetContextMenuUsed", SetContextMenuUsed },
			{ "GetUserData", GetUserData },
			{ "SetUserData", SetUserData },
			{ "GetTag", GetTag },
			{ "SetTag", SetTag },
			{ "GetTagCtrl", GetTagCtrl },
			{ "SetTagCtrl", SetTagCtrl },
			{ "IsVisible", IsVisible },
			{ "SetVisible", SetVisible },
			{ "SetInternVisible", SetInternVisible },
			{ "IsEnabled", IsEnabled },
			{ "SetEnabled", SetEnabled },
			{ "IsMouseEnabled", IsMouseEnabled },
			{ "SetMouseEnabled", SetMouseEnabled },
			{ "IsKeyboardEnabled", IsKeyboardEnabled },
			{ "SetKeyboardEnabled", SetKeyboardEnabled },
			{ "IsFocused", IsFocused },
			{ "SetFocus", SetFocus },
			{ "IsFloat", IsFloat },
			{ "SetFloat", SetFloat },
			{ "Invalidate", Invalidate },
			{ "IsUpdateNeeded", IsUpdateNeeded },
			{ "NeedUpdate", NeedUpdate },
			{ "NeedParentUpdate", NeedParentUpdate },
			{ "GetAdjustColor", GetAdjustColor },
			{ "SetAttribute", SetAttribute },
			{ "ApplyAttributeList", ApplyAttributeList },
			{ "EstimateSize", EstimateSize },
			{ "SetVirtualWnd", SetVirtualWnd },
			{ "GetVirtualWnd", GetVirtualWnd },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));

		lua_pop(l, 1);
	}
}
