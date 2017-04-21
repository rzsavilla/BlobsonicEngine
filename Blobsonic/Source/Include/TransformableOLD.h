#pragma once

/*! \class Transformable
Abstract class that gives object attributes to move around in 3D Space and apply transformations to it
*/

#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <stdafx.h>
#include "Component.h"


class Transformable {
protected:
	glm::vec3 m_vPosition;			//!< Objects position x,y,z
	glm::vec3 m_vRotation;			//!< Objects rotation x,y,z
	glm::vec3 m_vOrigin;			//!< Objects origin x,y,z
	glm::vec3 m_vScale;				//!< Objects scale facto x,y,z Default value at 1.0f
	glm::mat3 m_rotationMatrix;		//!< Rotation matrix
	bool m_bUpdated;				//!< Flag, member variable has been changed
public:
	Transformable() {}				//!< Default Contstructor

	//void init();

	//
	//void update(float dt);
	//void sendMessage(const Message msg);
	//void handleMessage(Message* msg);

	//void move(glm::vec3 vector);	//!< Adds vector to current position
	//void rotate(glm::vec3 vector);	//!< Adds vector to current rotation
	//void scale(glm::vec3 vector);	//!< Adds vector to current scale

	//void rotateX(float x);	 // Adds parameter to curent X rotation
	//void rotateY(float y);	 // Adds parameter to curent Y rotation
	//void rotateZ(float z);	 // Adds parameter to curent Z rotation

	//void setPosition(const glm::vec3 newPosition);	//!< The new value to m_vPosition
	//void setRotation(const glm::vec3 newRotation);	//!< The new value to m_vRotation
	//void setRotation(float deg, Axis);
	//void setOrigin(const glm::vec3 newOrigin);		//!< The new value to m_vOrigin
	//void setScale(const glm::vec3 newScale);		//!< The new value to m_vScale

	//void setScale(const float newScale);			//!< Set all elements of m_vScale to parameter

	//void setPosition(const float x, const float y, const float z);	//!< Set the position of the object 
	//void setRotation(const float x, const float y, const float z);	//!< Set Objects rotation in 3D space
	//void setOrigin(const float x, const float y, const float z);	//!< Set the Objects origin 
	//void setScale(const float x, const float y, const float z);		//!< Set scale of the object

	//glm::vec3 getPosition();			//!< Return position
	//glm::vec3 getRotation();			//!< Return rotation
	//glm::vec3 getOrigin();				//!< Return Origin

	//glm::mat4 getTransform();			//!< Returns transformation matrix
};


#endif