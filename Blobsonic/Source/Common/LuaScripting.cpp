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

	//Lua Scripting system functions
	lua.set("LuaScripting", LuaScripting());
	//-----Scene Management-----
	lua.set_function("setLoadingScene", &LuaScripting::setLoadingScene,LuaScripting());
	lua.set_function("reloadScene", &LuaScripting::reloadScene, LuaScripting());
	lua.set_function("changeScene", &LuaScripting::changeScene, LuaScripting());
	lua.set_function("forceReloadScene", &LuaScripting::forceReloadScene, LuaScripting());
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
	SceneManager::getInstance()->changeScene(sceneFile, true);
}

void System::Scripting::LuaScripting::reloadScene()
{
	m_bReloadScene = true;
	m_bReloadScripts = true;
	SceneManager::getInstance()->changeScene((SceneManager::getInstance()->getActiveSceneName()), false);
}

void System::Scripting::LuaScripting::forceReloadScene()
{
	m_bReloadScene = true;
	m_bReloadScripts = true;
	SceneManager::getInstance()->changeScene((SceneManager::getInstance()->getActiveSceneName()), true);
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
	else glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CROSSHAIR_CURSOR);		//Show Mouse
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
		m_bReloadScene = false;
	}
	//-----Game loop/run-------------------------------
	else if ((m_SceneManager->getState() == Active)) {
		//Use Run script
		if (m_bReloadScripts) {
			std::cout << "\n-----Initializing Scripts-----\n";
			m_RunState = luaL_newstate();
			LuaHelper::loadLibraries(m_RunState);

			registerClasses(m_RunState);
			registerFunctions(m_RunState);

			LuaHelper::loadScriptFile(m_RunState, (m_scriptsDir + "variables.lua"));
			//LuaHelper::loadScriptFile(m_RunState, (m_scriptsDir + "run.lua"));
			m_bReloadScripts = false;
		}
		else {
			if (m_RunState) {
				LuaHelper::loadScriptFile(m_RunState, (m_scriptsDir + "run.lua"));
			}
		}
	}
}

void System::Scripting::LuaScripting::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{
	/*for (auto it = msgs->begin(); it != msgs->end(); ++it) {

	}*/
}


/*
void System::Scripting::LuaScripting::readRootTable(lua_State * L)
{
std::cout << "-------Reading Root--------\n";
sol::state_view lua(L);	//Convert to sol state
sol::table root = lua["root"];

lua_pushnil(L);  // first key
//Iterate through tables elements --Looks at keys--
for (auto it = root.begin(); it != root.end(); ++it) {
auto key = (*it).first;
//--Process only string keys--
if (key.get_type() == sol::type::string) {
std::string s = key.as<std::string>();
if (m_bDebug) std::cout << "Key: " << s << " = ";

//--Get value of table element--
auto value = (*it).second;
switch (value.get_type())
{
case sol::type::string: {
std::string sValue = value.as<std::string>();
if (m_bDebug) std::cout << sValue << "-----\n";
break;
}
case sol::type::function: {
break;
}
case sol::type::boolean: {
//if (m_bDebug) std::cout << "-----Boolean-----\n";
break;
}
case sol::type::table: {
if (m_bDebug) std::cout << "Table\n";
if (s == "Entity") {
sol::table t = value.as<sol::table>();
//Create entity and pass message to add entity to the active scene
MessageHandler::getInstance()->sendMessage(std::make_shared<SceneMessage::AddEntity>(readEntity(t)));
}
break;
}
default:
std::cout << "\n";
break;
}
}
}
}
*/

/*
std::shared_ptr<Entity> System::Scripting::LuaScripting::readEntity(sol::table t)
{
std::shared_ptr<Entity> e = std::make_shared<Entity>();
for (auto it = t.begin(); it != t.end(); ++it) {
auto key = (*it).first;	//Get element key
//Processes ony strings
if (key.get_type() == sol::type::string) {
std::string s = key.as<std::string>();		//Get element value
std::cout << " " << s << "\n";
sol::table table = (*it).second.as<sol::table>();
//Attach Components
if (s == "Transformable") {
e->attach<Component::Transformable>(table);
}
else if (s == "Model") {
e->attach<Component::Model>(table);
}
}
}
return e;
}
*/
