#include "LuaEntry.h"

#include REQUIRE_H(CLabelUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CLabelUI, New)
	{
		CLabelUI  *ctrl = new CLabelUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CLabelUI, GetClassName)
	{
		CDuiString pstrText = CLabelUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CLabelUI, SetTextStyle)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			UINT uStyle = (UINT)lua_tointeger(l, 2);

			self->SetTextStyle(uStyle);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTextStyle"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, GetTextStyle)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			UINT uStyle = self->GetTextStyle();
			lua_pushinteger(l, (lua_Integer)uStyle);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTextStyle"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTextColor)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			self->SetTextColor(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTextColor"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, GetTextColor)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			
			DWORD dwBkCor = self->GetTextColor();
			
			LuaStatic::WriteRGBA2Lua(l, dwBkCor);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTextColor"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, SetDisabledTextColor)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			self->SetDisabledTextColor(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetDisabledTextColor"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, GetDisabledTextColor)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			
			DWORD dwBkCor = self->GetDisabledTextColor();
			
			LuaStatic::WriteRGBA2Lua(l, dwBkCor);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetDisabledTextColor"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, SetFont)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			int iFont = (int)lua_tointeger(l, 2);
			
			self->SetFont(iFont);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetFont"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, GetFont)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			int iFont = self->GetFont();
			lua_pushinteger(l, (lua_Integer)iFont);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetFont"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, GetTextPadding)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			RECT rt = self->GetTextPadding();

			LuaStatic::WriteRect2Lua(l, rt);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTextPadding"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, SetTextPadding)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			RECT rt = LuaStatic::ReadRectFromLua(l, 2);
			self->SetTextPadding(rt);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTextPadding"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, IsShowHtml)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, self->IsShowHtml() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::IsShowHtml"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, SetShowHtml)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			bool m = lua_toboolean(l, 2) != 0;

			self->SetShowHtml(m);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetShowHtml"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CLabelUI, SetEnabledEffect)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			bool m = lua_toboolean(l, 2) != 0;

			self->SetEnabledEffect(m);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetEnabledEffect"));
			return 0;
		}		
	}

	LUA_METHOD_IMPL(CLabelUI, GetEnabledEffect)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, self->GetEnabledEffect() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetEnabledEffect"));
			return 0;
		}
	}

	
	LUA_METHOD_IMPL(CLabelUI, SetTransShadow)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			self->SetTransShadow(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTransShadow"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTransShadow)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = self->GetTransShadow();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTransShadow"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTransShadow1)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			self->SetTransShadow1(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTransShadow1"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTransShadow1)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = self->GetTransShadow1();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTransShadow1"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTransText)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			self->SetTransText(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTransText"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTransText)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = self->GetTransText();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTransText"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTransText1)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			self->SetTransText1(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTransText1"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTransText1)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = self->GetTransText1();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTransText1"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTransStroke)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			self->SetTransStroke(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTransStroke"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTransStroke)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = self->GetTransStroke();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTransStroke"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetGradientLength)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			self->SetGradientLength(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetGradientLength"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetGradientLength)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = self->GetGradientLength();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetGradientLength"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTextRenderingHintAntiAlias)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = (int)lua_tointeger(l, 2);

			self->SetTextRenderingHintAntiAlias(size);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTextRenderingHintAntiAlias"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTextRenderingHintAntiAlias)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int size = self->GetTextRenderingHintAntiAlias();

			lua_pushinteger(l, (lua_Integer)size);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTextRenderingHintAntiAlias"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetShadowOffset)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			int offset = (int)lua_tointeger(l, 2);
			int angle = (int)lua_tointeger(l, 3);

			self->SetShadowOffset(offset, angle);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetShadowOffset"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetShadowOffset)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			Gdiplus::RectF rtmp = self->GetShadowOffset();
			RECT rt = {rtmp.X,rtmp.Y,rtmp.X+rtmp.Width,rtmp.Y+rtmp.Height};

			LuaStatic::WriteRect2Lua(l, rt);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetShadowOffset"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTextColor1)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			self->SetTextColor1(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTextColor1"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTextColor1)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			
			DWORD dwBkCor = self->GetTextColor1();
			
			LuaStatic::WriteRGBA2Lua(l, dwBkCor);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTextColor1"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTextShadowColorA)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			self->SetTextShadowColorA(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTextShadowColorA"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTextShadowColorA)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			
			DWORD dwBkCor = self->GetTextShadowColorA();
			
			LuaStatic::WriteRGBA2Lua(l, dwBkCor);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTextShadowColorA"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetTextShadowColorB)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			self->SetTextShadowColorB(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetTextShadowColorB"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetTextShadowColorB)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			
			DWORD dwBkCor = self->GetTextShadowColorB();
			
			LuaStatic::WriteRGBA2Lua(l, dwBkCor);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetTextShadowColorB"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetStrokeColor)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			DWORD dwBkCor = LuaStatic::ReadRGBAFromLua(l, 2);

			self->SetStrokeColor(dwBkCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetStrokeColor"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetStrokeColor)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			
			DWORD dwBkCor = self->GetStrokeColor();
			
			LuaStatic::WriteRGBA2Lua(l, dwBkCor);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetStrokeColor"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetGradientAngle)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			int _SetGradientAngle = (int)lua_tointeger(l, 2);

			self->SetGradientAngle(_SetGradientAngle);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetGradientAngle"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetGradientAngle)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			int _SetGradientAngle = self->GetGradientAngle();
			lua_pushinteger(l, (lua_Integer)_SetGradientAngle);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetGradientAngle"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetEnabledStroke)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			if (lua_isnone(l, 2))
				self->SetEnabledStroke(true);
			else
				self->SetEnabledStroke(0 != lua_toboolean(l, 2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetEnabledStroke"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetEnabledStroke)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, self->GetEnabledStroke() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetEnabledStroke"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, SetEnabledShadow)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));
			if (lua_isnone(l, 2))
				self->SetEnabledShadow(true);
			else
				self->SetEnabledShadow(0 != lua_toboolean(l, 2));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::SetEnabledShadow"));
			return 0;
		}
	}
	
	LUA_METHOD_IMPL(CLabelUI, GetEnabledShadow)
	{
		try
		{
			CLabelUI* self;
			self = static_cast<CLabelUI*>(LuaStatic::CheckUserData(l, 1));

			lua_pushboolean(l, self->GetEnabledShadow() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCLabelUI::GetEnabledShadow"));
			return 0;
		}
	}
	
	LUA_CLASS_REG_IMPL(CLabelUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "LabelUI");

		luaL_newmetatable(l, "CLabelUI");
		luaL_getmetatable(l, "CControlUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "SetTextStyle", SetTextStyle },
			{ "GetTextStyle", GetTextStyle },
			{ "SetTextColor", SetTextColor },
			{ "GetTextColor", GetTextColor },
			{ "SetDisabledTextColor", SetDisabledTextColor },
			{ "GetDisabledTextColor", GetDisabledTextColor },
			{ "SetFont", SetFont },
			{ "GetFont", GetFont },
			{ "GetTextPadding", GetTextPadding },
			{ "SetTextPadding", SetTextPadding },
			{ "SetShowHtml", SetShowHtml },
			{ "SetEnabledEffect", SetEnabledEffect },
			{ "GetEnabledEffect", GetEnabledEffect },
			{ "SetTransShadow", SetTransShadow },
			{ "GetTransShadow", GetTransShadow },
			{ "SetTransShadow1", SetTransShadow1 },
			{ "GetTransShadow1", GetTransShadow1 },
			{ "SetTransText", SetTransText },
			{ "GetTransText", GetTransText },
			{ "SetTransText1", SetTransText1 },
			{ "GetTransText1", GetTransText1 },
			{ "SetTransStroke", SetTransStroke },
			{ "GetTransStroke", GetTransStroke },
			{ "SetGradientLength", SetGradientLength },
			{ "GetGradientLength", GetGradientLength },
			{ "SetTextRenderingHintAntiAlias", SetTextRenderingHintAntiAlias },
			{ "GetTextRenderingHintAntiAlias", GetTextRenderingHintAntiAlias },
			{ "SetShadowOffset", SetShadowOffset },
			{ "GetShadowOffset", GetShadowOffset },
			{ "SetTextColor1", SetTextColor1 },
			{ "GetTextColor1", GetTextColor1 },
			{ "SetTextShadowColorA", SetTextShadowColorA },
			{ "GetTextShadowColorA", GetTextShadowColorA },
			{ "SetTextShadowColorB", SetTextShadowColorB },
			{ "GetTextShadowColorB", GetTextShadowColorB },
			{ "SetStrokeColor", SetStrokeColor },
			{ "GetStrokeColor", GetStrokeColor },
			{ "SetGradientAngle", SetGradientAngle },
			{ "GetGradientAngle", GetGradientAngle },
			{ "SetEnabledStroke", SetEnabledStroke },
			{ "GetEnabledStroke", GetEnabledStroke },
			{ "SetEnabledShadow", SetEnabledShadow },
			{ "GetEnabledShadow", GetEnabledShadow },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}

}