#include <stdafx.h>

#include "Engine.h"
#include "SceneComponent.h"

int main() {
	//Attach components to the engine
	Engine::getInstance()->attachComponent(std::make_unique<Render>());
	Engine::getInstance()->attachComponent(std::make_unique<SceneComponent>());
	Engine::getInstance()->init();		//Initialize engine
	Engine::getInstance()->run();		//Start engine

	return 0;
}