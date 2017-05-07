#include "stdafx.h"
#include "LuaScripting.h"
#include "Entity.h"

#include "MessageHandler.h"
#include "InputMessages.h"
#include "SceneMessages.h"

#include "Component.h"
#include "Transformable.h"
#include "Model.h"
#include "Player.h"
#include "LuaEntity.h"

#include "sol.hpp"

//Default values
bool System::Scripting::LuaScripting::m_bReloadScene = true;
bool System::Scripting::LuaScripting::m_bReloadScripts = true;

System::Scripting::LuaScripting::LuaScripting()
{
	m_SceneManager = SceneManager::getInstance();
}

void System::Scripting::LuaScripting::registerFunctions(lua_State * L)
{
	sol::state_view lua(L);

	//lua.set_function("changeScene", &Scripting::changeScene);
}

void System::Scripting::LuaScripting::registerClasses(lua_State * L)
{
	sol::state_view lua(L);

	//Timer Class
	lua.new_usertype<MyTimer>("Timer",
		"reset", &MyTimer::reset,
		"getElapsed",&MyTimer::getElapsed
	);


	//Lua Scripting system functions
	lua.set("LuaScripting", LuaScripting());
	//-----Scene Management-----
	lua.set_function("setLoadingScene", &LuaScripting::setLoadingScene,LuaScripting());
	lua.set_function("reloadScene", &LuaScripting::reloadScene, LuaScripting());
	lua.set_function("changeScene", &LuaScripting::changeScene, LuaScripting());
	lua.set_function("forceReloadScene", &LuaScripting::forceReloadScene, LuaScripting());
	lua.set_function("getActiveScene", &LuaScripting::getActiveScene, LuaScripting());
	lua.set_function("destroyEntity", &LuaScripting::destroyEntity, LuaScripting());
	//-----Inputs-----
	lua.set_function("isKeyDown", &LuaScripting::isKeyDown, LuaScripting());
	lua.set_function("isMouseDown", &LuaScripting::isMouseDown, LuaScripting());
	lua.set_function("hideCursor", &LuaScripting::hideCursor,LuaScripting());
	//-----Misc------
	lua.set_function("printString", &LuaScripting::printString, LuaScripting());
	lua.set_function("print", &LuaScripting::print, LuaScripting());
	//Register LuaEntity class
	LuaEntity::register_lua(lua);
}

void System::Scripting::LuaScripting::setLoadingScene(std::string sceneFile)
{
	SceneManager::getInstance()->setLoadingScene(sceneFile);
}

void System::Scripting::LuaScripting::changeScene(std::string sceneFile)
{
	//Stop scene from automatically switching to the loaded active scene
	//This is to allow the variables.lua file to initialize
	//SceneManager::getInstance()->lock(true);
	SceneManager::getInstance()->changeScene(sceneFile, true);
}

void System::Scripting::LuaScripting::reloadScene()
{
	m_bReloadScene = true;
	m_bReloadScripts = true;
	//SceneManager::getInstance()->lock(true);
	SceneManager::getInstance()->changeScene((SceneManager::getInstance()->getActiveSceneName()), false);
}

void System::Scripting::LuaScripting::forceReloadScene()
{
	m_bReloadScene = true;
	m_bReloadScripts = true;
	SceneManager::getInstance()->changeScene((SceneManager::getInstance()->getActiveSceneName()), true);
}

std::string System::Scripting::LuaScripting::getActiveScene()
{
	std::string s = SceneManager::getInstance()->getActiveSceneName();
	return s;
}

void System::Scripting::LuaScripting::destroyEntity(unsigned int ID)
{
	SceneManager::getInstance()->getActiveScene()->getEntityManager()->destroy(ID);	//Destroy entity by ID
}

bool System::Scripting::LuaScripting::isKeyDown(const std::string & key)
{
	int iKey = -1;

	if (key == "w" || key == "W") {
		iKey = GLFW_KEY_W;
	}
	else if (key == "s" || key == "S") {
		iKey = GLFW_KEY_S;
	}
	else if (key == "a" || key == "A") {
		iKey = GLFW_KEY_A;
	}
	else if (key == "d" || key == "D") {
		iKey = GLFW_KEY_D;
	}
	else if (key == "p" || key == "P") {
		iKey = GLFW_KEY_P;
	}
	else if (key == "o" || key == "O") {
		iKey = GLFW_KEY_O;
	}
	else if (key == "i" || key == "I") {
		iKey = GLFW_KEY_I;
	}

	else if (key == "up") iKey = GLFW_KEY_UP;
	else if (key == "down")	iKey = GLFW_KEY_DOWN;
	else if (key == "left")	iKey = GLFW_KEY_LEFT;
	else if (key == "right")iKey = GLFW_KEY_RIGHT;
	else if (key == "space") iKey = GLFW_KEY_SPACE;
	else if (key == "esc") iKey = GLFW_KEY_ESCAPE;

	if (iKey != -1) {
		if (glfwGetKey(glfwGetCurrentContext(), iKey)) {
			return true;
		}
	}
	return false;
}

bool System::Scripting::LuaScripting::isMouseDown(const std::string & button)
{
	int iButton = -1;
	if (button == "Left") {
		iButton = GLFW_MOUSE_BUTTON_LEFT;
	}
	else if (button == "Right") {
		iButton = GLFW_MOUSE_BUTTON_RIGHT;
	}

	if (iButton != -1) {
		if (glfwGetMouseButton(glfwGetCurrentContext(), iButton)) {
			return true;
		}
	}
	return false;
}

void System::Scripting::LuaScripting::hideCursor(bool hide)
{
	
	if (hide) glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//Hide mouse
	else glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);		//Show Mouse
}

void System::Scripting::LuaScripting::printString(const std::string & s)
{
	std::cout << s << "\n";
}

int System::Scripting::LuaScripting::print(lua_State * L)
{
	int nargs = lua_gettop(L);
	for (int i = 1; i <= nargs; ++i) {
		std::cout << lua_tostring(L, i);
	}
	std::cout << std::endl;

	return 0;
}

void System::Scripting::LuaScripting::process(std::vector<std::shared_ptr<Entity>>* entity)
{

}

void System::Scripting::LuaScripting::update(float dt)
{
	//-----Initial load/setup-------------------------------
	if (m_bReloadScene && (m_SceneManager->getState() == Active)) {
		
		lua_State* L = luaL_newstate();

		registerFunctions(L);
		registerClasses(L);
		
		sol::state_view lua(L);
		LuaHelper::loadScriptFile(L, (m_scriptsDir + "init.lua"));
		sol::load_result script = lua.load("a = 'test'");

		//Check if script is value
		if (!script.valid()) {
			if (m_bDebug) std::cout << "Failed to load script\n";
		}
		std::cout << "---Initial Script Loaded\n";
		m_bReloadScene = false;
	}
	//-----Run script-------------------------------
	else if (m_SceneManager->getState() == Active) {
		if (m_bReloadScripts) {
			m_RunState = luaL_newstate();
			LuaHelper::loadLibraries(m_RunState);
			registerClasses(m_RunState);
			registerFunctions(m_RunState);
			sol::state_view L(m_RunState);
			L.collect_garbage();
			LuaHelper::loadScriptFile(m_RunState, (m_scriptsDir + "variables.lua"));
			m_bReloadScripts = false;
		}
		else {
			registerClasses(m_RunState);
			registerFunctions(m_RunState);
			sol::state_view L(m_RunState);
			L.collect_garbage();
			LuaHelper::loadScriptFile(m_RunState, (m_scriptsDir + "run.lua"));
		}
		
	}
}

void System::Scripting::LuaScripting::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{

}