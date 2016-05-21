#include "LuaEntry.h"

#include REQUIRE_H(CDialogBuilder)

namespace DuiLib
{
	LUA_METHOD_IMPL(CDialogBuilder, isnil)
	{
		CDialogBuilder* self;
		self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));

		lua_pushboolean(l, self == NULL ? 1 : 0);
		return 1;
	}
	LUA_METHOD_IMPL(CDialogBuilder, _gc)
	{	
		CDialogBuilder* self;
		self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));
		LuaStatic::RemoveObjectInLua(l);
		SafeDelete(self);
		return 0;
	}
	LUA_METHOD_IMPL(CDialogBuilder, _eq)
	{
		try
		{
			CDialogBuilder* left;
			left = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));

			CDialogBuilder* right;
			right = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 2));

			lua_pushboolean(l, left == right ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCDialogBuilder::_eq"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CDialogBuilder, _tostring)
	{
		try
		{
			CDialogBuilder* self;
			self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));
			if (self)
			{
				CDuiString str = CDuiString::FormatString(_T("%s(addr:%p)"), self->GetClass(), (void*)self);
				lua_pushstring(l, str.GetAString().c_str());
			}
			else
			{
				CDuiString str = CDuiString::FormatString(_T("%s(addr:%s)"), "DialogBuilder", "nil");
				lua_pushstring(l, str.GetAString().c_str());
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCDialogBuilder::_tostring"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CDialogBuilder, Delete)
	{
		CRenderClip* self;
		self = static_cast<CRenderClip*>(LuaStatic::CheckUserData(l, 1));
		LuaStatic::RemoveObjectInLua(l);
		SafeDelete(self);
		return 0;
	}
	LUA_METHOD_IMPL(CDialogBuilder, New)
	{
		CDialogBuilder  *self = new CDialogBuilder();
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}
	LUA_METHOD_IMPL(CDialogBuilder, GetClassName)
	{
		CDuiString pstrText = CDialogBuilder::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CDialogBuilder, GetClass)
	{
		try
		{
			CDialogBuilder* self;
			self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetClass();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCDialogBuilder::GetClass"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CDialogBuilder, Create)
	{
		try
		{
			CDialogBuilder* self;
			self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));
			STRINGorID xml(_T(""));
			if (lua_isnumber(l,2))
				xml = STRINGorID(lua_tointeger(l, 2));
			else{
				CDuiString pstrText;
				lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

				xml = STRINGorID(pstrText.GetData());
			}

			CDuiString pType;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pType);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCDialogBuilder::Create"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CDialogBuilder, Create2)
	{
		try
		{
			CDialogBuilder* self;
			self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCDialogBuilder::Create2"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CDialogBuilder, GetMarkup)
	{
		try
		{
			CDialogBuilder* self;
			self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));
			CMarkup* pMarkup = self->GetMarkup();
			if (pMarkup)
				LuaStatic::AddObject2Lua(l, pMarkup, METATABLE_NAME(pMarkup));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCDialogBuilder::GetMarkup"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CDialogBuilder, GetLastErrorMessage)
	{
		try
		{
			CDialogBuilder* self;
			self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCDialogBuilder::GetLastErrorMessage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CDialogBuilder, GetLastErrorLocation)
	{
		try
		{
			CDialogBuilder* self;
			self = static_cast<CDialogBuilder*>(LuaStatic::CheckUserData(l, 1));

			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCDialogBuilder::GetLastErrorLocation"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CDialogBuilder)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "DialogBuilder");

		luaL_newmetatable(l, "CDialogBuilder");
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "isnil",isnil },
			{ "__eq",_eq },
			{ "__gc",_gc },
			{ "__tostring", _tostring },
			{ "GetClass", GetClass },
			{ "Create", Create },
			{ "Create2", Create2 },
			{ "GetMarkup", GetMarkup },
			{ "GetLastErrorMessage", GetLastErrorMessage },
			{ "GetLastErrorLocation", GetLastErrorLocation },
		};

		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}