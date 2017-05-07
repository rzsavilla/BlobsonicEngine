/**
*	@file ShadowMap.h
*	@class ShadowMap
*	@author Max Spencer-Hughes
*	@brief ShadowMap component
*	Shadow map light used to create shadows in the scene, not currently used
*/

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