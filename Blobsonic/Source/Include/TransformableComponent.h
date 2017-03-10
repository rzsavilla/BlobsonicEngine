/*
*	@struct Transformable
*	@brief Provides entity with transform matrix
*	Transform matrix for translation, rotation and scaling
*/

#pragma once

#include <stdafx.h>
#include "Component.h"

namespace Component {
	struct Transformable : public Component {
		Transformable() {
			m_transform = glm::mat4(1.0f);
			m_transform = glm::rotate(m_transform, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			m_fSpeed = 5.0f;
			m_fRotationSpeed = 0.1f;
			m_orienation = glm::quat(0.0f, 1.0f, 1.0f, 0.0f);
		};
		glm::mat4 m_transform;
		glm::quat m_orienation;
		float m_fSpeed;
		float m_fRotationSpeed;
	};
}