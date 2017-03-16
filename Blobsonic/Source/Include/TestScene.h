#pragma once

#include <stdafx.h>
#include <stdafx.h>
#include "Scene.h"

class TestScene: public Scene {
private:

public:
	TestScene();

	void initScene() override;

	void update(float dt) override;
};