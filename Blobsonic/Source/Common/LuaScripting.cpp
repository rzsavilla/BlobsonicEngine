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


void System::Scripting::LuaScripting::attachFunctions(lua_State * L)
{
	sol::state_view lua(L);

	//lua.set_function("changeScene", &Scripting::changeScene);
	lua.set_function("sayHello", &sayHello);

	lua.set_function("isKeyDown", &Scripting::isKeyDown);
	lua.set_function("isMouseDown", &Scripting::isMouseDown);

	lua.set_function("changeScene", &Scripting::changeScene);
	lua.set_function("setLoadingScene", &setLoadingScene);

	lua.set_function("reloadScene", &Scripting::reloadScene);
	lua.set_function("forceReloadScene", &Scripting::forceReloadScene);
}

void System::Scripting::LuaScripting::attachClasses(lua_State * L)
{
}
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

System::Scripting::LuaScripting::LuaScripting()
{
	MessageHandler::getInstance()->attachReceiver(this);
	m_SceneManager = SceneManager::getInstance();
}

void System::Scripting::LuaScripting::process(std::vector<std::shared_ptr<Entity>>* entity)
{

}

void System::Scripting::LuaScripting::update(float dt)
{
	if (!m_bLoaded && (m_SceneManager->getState() == Active)) {
		lua_State* L = luaL_newstate();

		attachClasses(L);
		attachFunctions(L);

		sol::state_view lua(L);
		LuaHelper::loadScriptFile(L, (m_scriptsDir + "init.lua"));
		sol::load_result script = lua.load("a = 'test'");

		//Check if script is value
		if (script.valid()) {
			if (m_bDebug) std::cout << "Script Loaded\n";
			//Look for root table
			sol::table rootTable = lua["root"];

			readRootTable(L);
		}
		else {
			if (m_bDebug) std::cout << "Failed to load script\n";
		}
		m_bLoaded = true;
	}
	else if ((m_SceneManager->getState() == Active)) {
		//Use Run script
		m_RunState = luaL_newstate();
		LuaHelper::loadLibraries(m_RunState);
		attachClasses(m_RunState);
		attachFunctions(m_RunState);
		LuaHelper::loadScriptFile(m_RunState, (m_scriptsDir + "run.lua"));
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

bool System::Scripting::isKeyDown(const std::string & key)
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
		iKey = GLFW_KEY_I;
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

bool System::Scripting::isMouseDown(const std::string & button)
{
	int iButton = -1;
	if (button == "Left") {
		iButton == GLFW_MOUSE_BUTTON_1;
	}
	else if (button == "Right") {
		iButton == GLFW_MOUSE_BUTTON_2;
	}

	if (iButton != -1) {
		if (glfwGetKey(glfwGetCurrentContext(), iButton)) {
			return true;
		}
	}
	return false;
}

void System::Scripting::changeScene(std::string sceneFile)
{
	SceneManager::getInstance()->changeScene(sceneFile,true);
}

void System::Scripting::setLoadingScene(std::string sceneFile)
{
	SceneManager::getInstance()->setLoadingScene(sceneFile);
}

void System::Scripting::reloadScene()
{
	SceneManager::getInstance()->changeScene((SceneManager::getInstance()->getActiveSceneName()),false);
}

void System::Scripting::forceReloadScene()
{
	SceneManager::getInstance()->changeScene((SceneManager::getInstance()->getActiveSceneName()),true);
}
