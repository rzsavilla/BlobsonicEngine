#pragma once

#include "sol.hpp"

namespace LuaHelper {
	void loadLibraries(lua_State* L);
	void loadScriptFile(lua_State* L, std::string filename);
}