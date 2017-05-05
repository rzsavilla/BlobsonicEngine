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
	lua_pcall(L, 0, 0, 0);             // call the script
}

glm::vec2 LuaHelper::readVec2(sol::object o)
{
	//Convert object to table
	sol::table t = o.as<sol::table>();
	//Read table variables
	return readVec2(t);
}

glm::vec3 LuaHelper::readVec3(sol::object o)
{
	//Convert object to table
	sol::table t = o.as<sol::table>();
	//Read table variables
	return readVec3(t);
}

glm::vec2 LuaHelper::readVec2(sol::table t)
{
	float fValue;
	glm::vec2 v;
	//Iterate through table elements
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		//Processes ony strings
		if (key.get_type() == sol::type::string) {
			std::string s = key.as<std::string>();		//Key
			auto value = (*it).second.as<float>();
			if (s == "x") v.x = value;
			else if (s == "y")	v.y = value;
		}
	}
	return v;
}

glm::vec3 LuaHelper::readVec3(sol::table t)
{
	float fValue;
	glm::vec3 v;
	//Iterate through table elements
	for (auto it = t.begin(); it != t.end(); ++it) {
		auto key = (*it).first;	//Get element key
		//Processes ony strings
		if (key.get_type() == sol::type::string) {
			std::string s = key.as<std::string>();		//Key
			auto value = (*it).second.as<float>();
			if (s == "x") v.x = value;
			else if (s == "y")	v.y = value;
			else if (s == "z")	v.z = value;
		}
	}
	return v;
}
