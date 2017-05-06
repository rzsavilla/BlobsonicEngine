#pragma once

#include "Light.h"

namespace Component {
	class ShadowMap : public Component, public Light {
	private:
		glm::mat4 m_mShadowMatrix;
		glm::vec3 m_vShadowCoords;
	public:
		ShadowMap();		//!< Default constructor

	};
}