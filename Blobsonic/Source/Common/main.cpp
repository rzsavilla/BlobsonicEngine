#include <stdafx.h>

#include "Engine.h"

#include "Render.h"
#include "CameraSystem.h"

int main() {
	//Attach systems to the engine

	Engine::Engine engine;

	engine.init(1024, 768);
	engine.attachSystem<System::Render>();			//Render objects
	engine.attachSystem<System::CameraSystem>();	//Control active camera
	engine.run();
	glfwTerminate();
	return 0;
}