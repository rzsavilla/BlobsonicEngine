/**
* @class	Scene
* @brief	Storage for scenes and determines active scene
* @author	Rozen Savilla
* Storage for loaded scenes ready to be activated
*/

#pragma once

#include "Component.h"
#include "Light.h"

namespace Component {
	class PointLight : public Component, public Light {
	private:
		float m_fRadius;
	public:
		PointLight();	//!< Default Contructor

		void setRadius(float radius);
		float getRadius();
	};
}