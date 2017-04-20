/*
*	@struct Transformable
*	@brief Provides entity with transform matrix
*	Transform matrix for translation, rotation and scaling
*	Gives entity a size (for collisions)
*/

#pragma once

#include <stdafx.h>
#include "Component.h"

namespace Component {
	struct Transformable : public Component {
		Transformable() {
			//m_transform = glm::mat4(1.0f);
			m_fSpeed = 5.0f;
			m_fRotationSpeed = 0.1f;
			m_orienation = glm::quat(0.0f, 1.0f, 1.0f, 0.0f);
		};
		//glm::mat4 m_transform;
		glm::quat m_orienation;
		float m_fSpeed;
		float m_fRotationSpeed;


		glm::vec3 m_vScale;
		glm::vec3 m_vDimensions;
		glm::vec3 m_vCenter;
		glm::vec3 m_vPosition;
		glm::vec3 m_vRotation;	//!< x,y,z rotation in radians
		glm::vec3 m_vOrigin;	//!< x,y,z origin

		void setScale(glm::vec3 Scale)
		{
			m_vDimensions = m_vDimensions * Scale;
			m_vScale = Scale;
		}

		void setPosition(glm::vec3 position) {
			m_vPosition = position;
		};

		void setRotation(glm::vec3 rotation) {
			m_vRotation = rotation;
		}

		glm::vec3 getPosition() {
			return m_vPosition;
		}

		glm::vec3 getScale() {
			return m_vScale;
		}

		glm::vec3 getRotation() {
			return m_vRotation;
		}

		glm::mat4 getTransform() {
			glm::mat4 t, s, r;	//Translation scale and rotation matrices
			s = glm::scale(glm::mat4(1.0f), getScale());									//Scale
			//t = glm::translate(glm::mat4(1.0f), getPosition());								//Translate
			t[3][0] = getPosition().x;
			t[3][1] = getPosition().y;
			t[3][2] = getPosition().z;
			t[3][3] = 1.0f;
			r = glm::rotate(glm::mat4(1.0f), getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));	//X rotation
			r = glm::rotate(r, getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));				//Y rotation
			r = glm::rotate(r, getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));				//Z rotation
			return t * r * s;
		}
	};
}