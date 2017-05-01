/*
	Code by eliasdaler
	https://github.com/eliasdaler/LuaInPractice2SourceCode/blob/master/LuaHelperFunctions.h
*/
#pragma once

#include <vector>

#include "LuaBridge.h"
using namespace luabridge;

namespace luah {
	bool loadScript(lua_State* L, const std::string& filename);
	void lua_gettostack(lua_State* L, const std::string& variableName);
	void loadGetKeysFunction(lua_State* L);
	std::vector<std::string> getTableKeys(lua_State* L, const std::string& name);
}