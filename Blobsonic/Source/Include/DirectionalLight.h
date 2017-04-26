#pragma once

#include "Component.h"
#include "Light.h"

namespace Component {
	class DirectionalLight :public Component, public Light {
	private:

	public:
		DirectionalLight();
	};
}