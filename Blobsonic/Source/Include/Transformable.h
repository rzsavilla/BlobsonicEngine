/*
*	@struct Transformable
*	@brief Provides entity with transform matrix
*	Transform matrix for translation, rotation and scaling
*/

#pragma once

#include "stdafx.h"
#include "Component.h"

static float fMyRotation = 0;

namespace Component {
	class Transformable : public Component {
	private:
		
	public:
		glm::vec3 m_vPosition;	//!< Camera World/Relative Position
		glm::vec3 m_vScale;		//!< Entity scale x,y,z
		glm::vec3 m_vRotation;	//!< x,y,z rotation in stored in degrees

		glm::vec3 m_vDimensions;	//Plz move to different component
		glm::vec3 m_vCenter;		
		
		glm::vec3 m_vOrigin;	//!< x,y,z origin currently not applied
	public:
		Transformable();					//!< Default Constructor
		float m_fSpeed;						//!< Temporary variable will be stored in separate component
		float m_fRotationSpeed;				//!< Temporary variable will be stored in separate component

		void setPosition(glm::vec3 position);	//!< Set Position
		void setRotation(glm::vec3 degrees);	//!< Set Rotation
		void setScale(glm::vec3 scale);			//!< Set Scale

		glm::vec3 getPosition();	//!< Returns position
		glm::vec3 getRotation();	//!< Returns rotation in degrees
		glm::vec3 getScale();		//!< Returns scale

		glm::mat4 getTransform();	//!< Returns transformation matrix
	};
}