#pragma once

#include <stdafx.h>
#include <stdafx.h>
#include "Scene.h"

class TestScene: public Scene {
private:

public:
	TestScene(ResourceManager* res);

	void initScene() override;

	void update(float dt) override;
};