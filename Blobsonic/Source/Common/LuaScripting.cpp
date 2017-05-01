#include "stdafx.h"
#include "LuaScripting.h"
#include "Entity.h"

#include "InputMessages.h"
#include "SceneMessages.h"

#include "Component.h"
#include "Transformable.h"

#include "Player.h"
#include "LuaEntity.h"

using namespace luabridge;

bool System::Scripting::LuaScripting::loadScript(std::string luaFile)
{
	if (m_bDebug) std::cout << "\n----------Loading Script: " << luaFile << " -------------\n";
	m_luaState = luaL_newstate();

	luaL_openlibs(m_luaState);		//Openg libs

	if (!(luabridge::luaL_loadfile(m_luaState, (m_scriptsDir + luaFile).c_str()) || luabridge::lua_pcall(m_luaState, 0, 0, 0))) {
		if (m_bDebug)std::cout << "Script Loaded: " << (m_scriptsDir + luaFile) << std::endl;
		return true;
	}
	else {
		std::cout << "Could not load lua script: " << (m_scriptsDir + luaFile) << "\n";
		std::cout << lua_tostring(m_luaState, -1) << std::endl;
		lua_pop(m_luaState, 1); // pop the error message from stack
		return false;
	}
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

std::shared_ptr<Entity> System::Scripting::LuaScripting::loadEntity(lua_State* L, std::string type)
{
	auto e = std::make_shared<Entity>();
	if (m_bDebug) std::cout << "Creating Entity: " << e->getUID() << "\n";
	auto v = luah::getTableKeys(L, type);
	for (auto &component : v) {
		if (component == "Transformable") {
			e->attach<Component::Transformable>();
		}
		if (m_bDebug) std::cout << " Attached -" << component << "\n";
	}

	return e;
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
		if (loadScript("init.lua")) {
			m_luaState = luaL_newstate();
			luah::loadScript(m_luaState,(m_scriptsDir + "init.lua").c_str());
			luah::loadGetKeysFunction(m_luaState);

			auto e = loadEntity(m_luaState, "box");
		}
		m_bLoaded = true;
		lua_close(m_luaState);
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
