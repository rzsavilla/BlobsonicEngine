#include "stdafx.h"
#include "LuaScripting.h"

void System::Scripting::LuaScripting::loadScript(std::string luaFile)
{
	m_luaState = luaL_newstate();

	luaL_openlibs(m_luaState);		//Openg libs
			
	registerFunctions();	//Attach functions

	//Check if lua file loaded
	if (luaL_dofile(m_luaState, (m_scriptsDir + luaFile).c_str()) != 0) {
		lua_pcall(m_luaState, 0, 0, 0);
		std::cout << "Could not load lua script: " << (m_scriptsDir + luaFile) << "\n";
	}
	else {
		std::cout << "Script Loaded: " << (m_scriptsDir + luaFile) << std::endl;
	}
}

void System::Scripting::LuaScripting::registerFunctions()
{

}

std::shared_ptr<Entity> System::Scripting::LuaScripting::Entity_new(lua_State * L)
{
	const char* name = luaL_checkstring(L, 1);
	return std::make_shared<Entity>();
}

System::Scripting::LuaScripting::LuaScripting()
{
	loadScript("init.lua");
}

void System::Scripting::LuaScripting::process(std::vector<std::shared_ptr<Entity>>* entity)
{

}

void System::Scripting::LuaScripting::update(float dt)
{

}

void System::Scripting::LuaScripting::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{

}
