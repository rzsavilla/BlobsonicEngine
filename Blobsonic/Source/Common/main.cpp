#include "stdafx.h"

#include "Engine.h"

#include "Render.h"
#include "CameraSystem.h"
#include "PlayerController.h"
#include "Physics.h"
#include "CameraController.h"
#include "Gameplay.h"
#include "Audio.h"
#include "LuaScripting.h"
#include "GUI.h"
#include "Gameover.h"

int main() {
	//Attach systems to the engine
	Engine::Engine engine;

	engine.init(1600, 900);
	engine.attachSystem<System::Render>();				//Render objects
	//engine.attachSystem<System::CameraSystem>();		//Control active camera
	engine.attachSystem<System::Physics>();				//Do physics check on scene
	engine.attachSystem<System::Audio>();				//Start audio objects
	engine.attachSystem<System::PlayerController>();	//Control player character
	engine.attachSystem<System::CameraController>();
	engine.attachSystem<System::Gameplay>();
	engine.attachSystem<System::Scripting::LuaScripting>();
	engine.attachSystem<System::GUI>();
	engine.attachSystem<System::Gameover>();
	engine.run();
	return 0;
}