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
			m_fSpeed = 5.0f;
			m_fRotationSpeed = 0.1f;
			m_orienation = glm::quat(0.0f, 1.0f, 1.0f, 0.0f);
		};
		glm::mat4 m_transform;
		glm::quat m_orienation;
		float m_fSpeed;
		float m_fRotationSpeed;


		glm::vec3 m_vScale;
		glm::vec3 m_vDimensions;
		glm::vec3 m_vCenter;
		glm::vec3 m_vPosition;

		void setPosition(glm::vec3 position) {
			m_transform[3][0] = position.x;
			m_transform[3][1] = position.y;
			m_transform[3][2] = position.z;
		};

		glm::vec3 getPosition() {
			return glm::vec3(
				m_transform[3][0],
				m_transform[3][1],
				m_transform[3][2]
			);
		}
	};
}