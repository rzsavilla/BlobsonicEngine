#include "stdafx.h"
#include "Transformable.h"

Component::Transformable::Transformable() 
{
	m_vPosition = glm::vec3(0.0f);
	m_vRotation = glm::vec3(0.0f);
	m_vScale = glm::vec3(1.0f);

	m_vOrigin = glm::vec3(0.0f);
}

void Component::Transformable::setPosition(glm::vec3 position)
{
	m_vPosition = position;
}

void Component::Transformable::setRotation(glm::vec3 degrees)
{
	m_vRotation = glm::radians(degrees);
}

void Component::Transformable::setScale(glm::vec3 scale)
{
	m_vScale = scale;
}

glm::vec3 Component::Transformable::getPosition()
{
	return m_vPosition;
}

glm::vec3 Component::Transformable::getRotation()
{
	return glm::degrees(m_vRotation);
}

glm::vec3 Component::Transformable::getScale()
{
	return m_vScale;
}

glm::mat4 Component::Transformable::getTransform()
{
	glm::mat4 t, s, r;	//Translation scale and rotation matrices
	s = glm::scale(glm::mat4(1.0f), getScale());									//Scale
	t = glm::translate(glm::mat4(1.0f), getPosition());								//Translate

	//Rotations applied are in radians
	r = glm::rotate(glm::mat4(1.0f), m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));	//X rotation
	r = glm::rotate(r, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));					//Y rotation
	r = glm::rotate(r, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));					//Z rotation

	return t * r * s;
}
