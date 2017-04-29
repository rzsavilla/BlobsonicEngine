#include "stdafx.h"
#include "LuaScripting.h"


void printMessage(const std::string& s) {
	std::cout << s << std::endl;
}

void System::LuaScripting::loadScript(std::string luaFile)
{
	//Load script file
	luaL_dofile(m_luaState, luaFile.c_str());

	//load lua libs
	luaL_openlibs(m_luaState);

	getGlobalNamespace(m_luaState).
		addFunction("printMessage", printMessage);

	//Check if lua file loaded
	if (luaL_loadfile(m_luaState, luaFile.c_str())) {
		//call lua script
		lua_pcall(m_luaState, 0, 0, 0);
	}

	if (luaL_dofile(m_luaState, luaFile.c_str()) != 0) {
		lua_pcall(m_luaState, 0, 0, 0);
		std::cout << "Could not load file: " << luaFile << std::endl;
	}
	else {
		std::cout << "Script Loaded" << std::endl;
	}
}

void System::LuaScripting::addFunctions()
{

}

void System::LuaScripting::helloWorld()
{

}

void sayHello(const std::string& s) {
	std::cout << s << std::endl;
}

System::LuaScripting::LuaScripting()
{
	m_luaState = luaL_newstate();

	//loadScript("script.lua");
	
	lua_State* L = luaL_newstate();
	//Openg libs
	luaL_openlibs(L);

	//Attach functions
	addFunctions();
	getGlobalNamespace(L).
		addFunction("sayHello", &sayHello);

	//Load Script
	luaL_dofile(L, "script.lua");
	lua_pcall(L, 0, 0, 0);

	//Get Variable
	LuaRef s = getGlobal(L, "testString");
	LuaRef n = getGlobal(L, "number");

	std::string luaString = s.cast<std::string>();

	int answer = n.cast<int>();
	std::cout << luaString << std::endl;
	std::cout << "And here's our number:" << answer << std::endl;
}

void System::LuaScripting::process(std::vector<std::shared_ptr<Entity>>* entity)
{

}

void System::LuaScripting::update(float dt)
{

}

void System::LuaScripting::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{

}
