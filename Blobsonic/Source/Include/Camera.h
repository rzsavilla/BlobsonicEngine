#pragma once

#include <stdafx.h>
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Component {
	struct Camera {
		Camera() {
			m_fFieldOfView = glm::radians(90.0f);
			m_fNearPlane = 0.01f;
			m_fFarPlane = 1000.0f;
			m_fAspectRatio = 4.0f / 3.0f;;

			m_vAxisX = glm::vec3(0.0f);
			m_vAxisY = glm::vec3(0.0f);
			m_vAxisZ = glm::vec3(0.0f);

			m_vPosition = glm::vec3(0.0f, 0.0f, 5.0f);

			m_qOrientation = glm::quat(1.0, 0.0, 0.0, 0.0);
			m_projection = glm::perspective(m_fFieldOfView, m_fAspectRatio, m_fNearPlane, m_fFarPlane);

			m_view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, 10.0f),	//Pos
				glm::vec3(0.0f, 0.0f, 0.0f),	//Dir
				glm::vec3(0.0f, 1.0f, 0.0f)		//Up
			);
				

			m_fMoveSpeed = 5.0f;

			m_bActive = false;

			m_bFollowTarget = false;
			m_vTarget = glm::vec3(0.0f);
			m_vCameraDist = glm::vec3(0.0f, 300.0f, 100.0f);
		};

		float m_fFieldOfView;
		float m_fNearPlane;
		float m_fFarPlane;
		float m_fAspectRatio;

		//Camera coordinate axis
		glm::vec3 m_vAxisX;
		glm::vec3 m_vAxisY;
		glm::vec3 m_vAxisZ;

		glm::vec3 m_vPosition;

		glm::quat m_qOrientation;
		glm::mat4 m_view;
		glm::mat4 m_projection;

		bool m_bActive;	//!< Render uses this camera when active
		float m_fMoveSpeed;
		bool m_bFollowTarget;

		glm::vec3 m_vTarget;
		glm::vec3 m_vCameraDist;	//!< Camera distance from target
	};
}