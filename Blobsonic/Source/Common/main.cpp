#include "stdafx.h"

#include "Engine.h"

#include "Render.h"
#include "CameraSystem.h"
#include "PlayerController.h"
#include "Physics.h"
#include "CameraController.h"
#include "Gameplay.h"
#include "LuaScripting.h";

int main() {
	//Attach systems to the engine

	Engine::Engine engine;

	engine.init(1024, 768);
	engine.attachSystem<System::Render>();				//Render objects
	engine.attachSystem<System::CameraSystem>();		//Control active camera
	engine.attachSystem<System::Physics>();				//Do physics check on scene
	engine.attachSystem<System::PlayerController>();	//Control player character
	engine.attachSystem<System::CameraController>();
	engine.attachSystem<System::Gameplay>();
	engine.attachSystem<System::LuaScripting>();
	engine.run();
	return 0;
}

////Code to test if lua and luabridge is successfuly
//using namespace luabridge;
//int main() {
//	lua_State* L = luaL_newstate();
//	luaL_dofile(L, "script.lua");
//	luaL_openlibs(L);
//	lua_pcall(L, 0, 0, 0);
//	LuaRef s = getGlobal(L, "testString");
//	LuaRef n = getGlobal(L, "number");
//	std::string luaString = s.cast<std::string>();
//	int answer = n.cast<int>();
//	std::cout << luaString << std::endl;
//	std::cout << "And here's our number:" << answer << std::endl;
//	system("pause");
//}