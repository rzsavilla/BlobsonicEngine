#include <stdafx.h>

#include "Engine.h"

#include "Render.h"
#include "CameraSystem.h"
#include "PlayerController.h"
#include "Physics.h"
#include "CameraController.h"

int main() {
	//Attach systems to the engine

	Engine::Engine engine;

	engine.init(1024, 768);
	engine.attachSystem<System::Render>();				//Render objects
	//engine.attachSystem<System::CameraSystem>();		//Control active camera
	//engine.attachSystem<System::Physics>();				//Do physics check on scene
	//engine.attachSystem<System::PlayerController>();	//Control player character
	engine.attachSystem<System::CameraController>();
	engine.run();
	glfwTerminate();
	return 0;
}