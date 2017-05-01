#pragma once

#include "sol.hpp"

namespace LuaHelper {
	void loadLibraries(lua_State* L);
	void loadScriptFile(lua_State* L, std::string filename);

	glm::vec2 readVec2(sol::object o);
	glm::vec3 readVec3(sol::object o);
	glm::vec2 readVec2(sol::table t);
	glm::vec3 readVec3(sol::table t);
}