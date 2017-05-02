/**
* @class	Scene
* @brief	Directional Light Component
* @author	Rozen Savilla
* Stores light variables
*/

#pragma once

#include "Component.h"
#include "Light.h"

namespace Component {
	class DirectionalLight :public Component, public Light {
	private:
		glm::vec3 m_vDirection;
	public:
		DirectionalLight();

		void setDirection(glm::vec3 dir);

		glm::vec3 getDirection();;
	};
}