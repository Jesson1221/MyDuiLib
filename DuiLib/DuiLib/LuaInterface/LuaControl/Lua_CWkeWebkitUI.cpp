#include "LuaEntry.h"

#include REQUIRE_H(CWkeWebkitUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CWkeWebkitUI, New)
	{
		CWkeWebkitUI  *ctrl = new CWkeWebkitUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CWkeWebkitUI, GetClassName)
	{
		CDuiString pstrText = CWkeWebkitUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}


	LUA_METHOD_IMPL(CWkeWebkitUI,WkeWebkit_Init)
	{
		try
		{
			CWkeWebkitUI::WkeWebkit_Init();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::WkeWebkit_Init"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CWkeWebkitUI,WkeWebkit_Shutdown)
	{
		try
		{
			CWkeWebkitUI::WkeWebkit_Shutdown();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::WkeWebkit_Shutdown"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CWkeWebkitUI,SetURL)
	{
		try
		{
			CWkeWebkitUI* self;
			self = static_cast<CWkeWebkitUI*>(LuaStatic::CheckUserData(l, 1));
			std::string s;
			lua_op_t<std::string>::lua_to_value(l,2,s);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::SetURL"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CWkeWebkitUI,SetFile)
	{
		try
		{
			CWkeWebkitUI* self;
			self = static_cast<CWkeWebkitUI*>(LuaStatic::CheckUserData(l, 1));
			std::string s;
			lua_op_t<std::string>::lua_to_value(l,2,s);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::SetFile"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CWkeWebkitUI,RunJS)
	{
		try
		{
			CWkeWebkitUI* self;
			self = static_cast<CWkeWebkitUI*>(LuaStatic::CheckUserData(l, 1));
			std::string s;
			lua_op_t<std::string>::lua_to_value(l,2,s);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::CreateControl2"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CWkeWebkitUI,SetClientHandler)
	{
		try
		{
			CWkeWebkitUI* self;
			self = static_cast<CWkeWebkitUI*>(LuaStatic::CheckUserData(l, 1));
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::SetClientHandler"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CWkeWebkitUI,GoBack)
	{
		try
		{
			CWkeWebkitUI* self;
			self = static_cast<CWkeWebkitUI*>(LuaStatic::CheckUserData(l, 1));
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::GoBack"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CWkeWebkitUI,GoForward)
	{
		try
		{
			CWkeWebkitUI* self;
			self = static_cast<CWkeWebkitUI*>(LuaStatic::CheckUserData(l, 1));
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::GoForward"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CWkeWebkitUI,GoHome)
	{
		try
		{
			CWkeWebkitUI* self;
			self = static_cast<CWkeWebkitUI*>(LuaStatic::CheckUserData(l, 1));
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCWkeWebkitUI::GoHome"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CWkeWebkitUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
			{ "WkeWebkit_Init", WkeWebkit_Init },
			{ "WkeWebkit_Shutdown", WkeWebkit_Shutdown },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "WkeWebkitUI");

		luaL_newmetatable(l, "CWkeWebkitUI");
		luaL_getmetatable(l, "CControlUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "SetURL", SetURL },
			{ "SetFile", SetFile },
			{ "RunJS", RunJS },
			{ "SetClientHandler", SetClientHandler },
			{ "GoBack", GoBack },
			{ "GoForward", GoForward },
			{ "GoHome", GoHome },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}