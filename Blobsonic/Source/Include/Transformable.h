/*
*	@class Transformable
*	@brief Provides entity with transform matrix
*	@author Rozen Savilla
*	Transform matrix for translation, rotation scaling and origin.
*	Transformable component is the core component for majority of all entities as it gives the entity a position in world space
*	Gives entity a size (for collisions) -- To be removed
*/

#pragma once

#include "stdafx.h"
#include "Component.h"
#include "sol.hpp"

namespace Component {
	class Transformable : public Component {
	private:
		bool m_bDebug = true;	//!< Flag for couts
	public:
		glm::vec3 m_vPosition;	//!< Camera World/Relative Position
		glm::vec3 m_vScale;		//!< Entity scale x,y,z
		glm::vec3 m_vRotation;	//!< x,y,z rotation in stored in degrees
		glm::vec3 m_vOrigin;	//!< x,y,z origin currently not applied
	public:
		Transformable();				//!< Default Constructor
		Transformable(sol::table t);	//!< Constructor that reads lua table data to set initial parameters
		float m_fSpeed;				//!< Temporary variable will be stored in separate component
		float m_fRotationSpeed;		//!< Temporary variable will be stored in separate component

		void translate(float x, float y, float z);	//!< Increase current position by parameter values
		void rotate(float x, float y, float z);		//!< Increase current rotation by parameter values
		void scale(float x, float y, float z);		//!< Increase current scale by parameter values
		void translateV(glm::vec3 translation);		//!< Increase current position by parameter values
		void rotateV(glm::vec3 rotation);			//!< Increase current rotation by parameter values
		void scaleV(glm::vec3 scale);				//!< Increase current scale by parameter values

		void setPosition(glm::vec3 position);	//!< Set Position
		void setRotation(glm::vec3 degrees);	//!< Set Rotation
		void setScale(glm::vec3 scale);			//!< Set Scale
		void setOrigin(glm::vec3 origin);		//!< Set Origin

		glm::vec3 getPosition();	//!< Returns position
		glm::vec3 getRotation();	//!< Returns rotation in degrees
		glm::vec3 getScale();		//!< Returns scale
		glm::vec3 getOrigin();		//!< Returns origin

		glm::mat4 getTransform();	//!< Returns transformation matrix

		/*! Register this C++ class as a lua class
			Allows lua access to member functions
		*/
		static void register_lua(sol::state_view L);

		sol::object getTable(sol::state_view L);
	};
}