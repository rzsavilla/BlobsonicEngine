#include "stdafx.h"
#include "LuaHelper.h"

void LuaHelper::loadLibraries(lua_State * L)
{
	sol::state_view lua(L);
	lua.open_libraries(sol::lib::base, sol::lib::package);
}

void LuaHelper::loadScriptFile(lua_State * L, std::string filename)
{
	sol::state_view lua(L);
	lua.script_file(filename);
}
