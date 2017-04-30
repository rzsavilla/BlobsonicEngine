#include "stdafx.h"
#include "LuaScripting.h"
#include "Entity.h"

#include "InputMessages.h"
#include "SceneMessages.h"

#include "Component.h"
#include "Transformable.h"

#include "Player.h"
#include "LuaEntity.h"

void System::Scripting::LuaScripting::loadScript(std::string luaFile)
{
	if (m_bDebug) std::cout << "\n----------Loading Script: " << luaFile << " -------------\n";
	m_luaState = luaL_newstate();

	luaL_openlibs(m_luaState);		//Openg libs
			
	registerFunctions(m_luaState);	//Attach functions
	registerClasses(m_luaState);	//Attach classes

	//Check if lua file loaded
	if (luaL_dofile(m_luaState, (m_scriptsDir + luaFile).c_str())) {
		std::cout << "Could not load lua script: " << (m_scriptsDir + luaFile) << "\n";
		return;
	}
	if (m_bDebug)std::cout << "Script Loaded: " << (m_scriptsDir + luaFile) << std::endl;
	lua_pcall(m_luaState, 0, 0, 0);
}

void System::Scripting::LuaScripting::registerFunctions(lua_State * L)
{
	getGlobalNamespace(L).addFunction("LuaLoaded", &LuaLoaded);
}

void System::Scripting::LuaScripting::registerClasses(lua_State * L)
{
	using namespace Component;

	LuaEntity::register_lua(L);
}

System::Scripting::LuaScripting::LuaScripting()
{
	MessageHandler::getInstance()->attachReceiver(this);
}

void System::Scripting::LuaScripting::process(std::vector<std::shared_ptr<Entity>>* entity)
{

}

void System::Scripting::LuaScripting::update(float dt)
{
	if (!m_bLoaded) {
		loadScript("init.lua");
		m_bLoaded = true;
	}
}

void System::Scripting::LuaScripting::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	for (auto it = msgs->begin(); it != msgs->end(); ++it) {
		if ((*it)->sID == "Scene_Reload") {
			//Reload scripts
			std::cout << "Reload Scripts\n";
			if (m_bLoaded) m_bLoaded = false;
		}
	}
}
