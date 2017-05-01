#include "stdafx.h"
#include "Transformable.h"

#include <glm/gtc/type_ptr.hpp>	//make_vec3

Component::Transformable::Transformable() 
{
	m_vPosition = glm::vec3(0.0f);
	m_vRotation = glm::vec3(0.0f);
	m_vScale = glm::vec3(1.0f);

	m_vOrigin = glm::vec3(0.0f);
}

void Component::Transformable::translate(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

void Component::Transformable::rotate(float x, float y, float z)
{
	m_vRotation.x += x;
	m_vRotation.y += y;
	m_vRotation.z += z;
}

void Component::Transformable::scale(float x, float y, float z)
{
	m_vScale.x += x;
	m_vScale.y += y;
	m_vScale.z += z;
}

void Component::Transformable::translate(glm::vec3 translation)
{
	m_vPosition += translation;
}

void Component::Transformable::rotate(glm::vec3 rotation)
{
	m_vRotation += rotation;
}

void Component::Transformable::scale(glm::vec3 scale)
{
	m_vScale += scale;
}

void Component::Transformable::setPosition(glm::vec3 position)
{
	m_vPosition = position;
}

void Component::Transformable::setRotation(glm::vec3 degrees)
{
	m_vRotation = degrees;
}

void Component::Transformable::setScale(glm::vec3 scale)
{
	m_vScale = scale;
}

void Component::Transformable::setOrigin(glm::vec3 origin)
{
	m_vOrigin = origin;
}

glm::vec3 Component::Transformable::getPosition()
{
	return m_vPosition;
}

glm::vec3 Component::Transformable::getRotation()
{
	return m_vRotation;
}

glm::vec3 Component::Transformable::getScale()
{
	return m_vScale;
}

glm::vec3 Component::Transformable::getOrigin()
{
	return m_vOrigin;
}

glm::mat4 Component::Transformable::getTransform()
{
	glm::mat4 t, s, r,o;	//Translation scale and rotation matrices
	s = glm::scale(glm::mat4(1.0f), getScale());									//Scale
	t = glm::translate(glm::mat4(1.0f), getPosition());								//Translate

	//Rotations applied are in radians
	glm::vec3 rad = glm::radians(getRotation());
	r = glm::rotate(glm::mat4(1.0f), rad.x, glm::vec3(1.0f, 0.0f, 0.0f));	//X rotation
	r = glm::rotate(r, rad.y, glm::vec3(0.0f, 1.0f, 0.0f));					//Y rotation
	r = glm::rotate(r, rad.z, glm::vec3(0.0f, 0.0f, 1.0f));					//Z rotation

	o = glm::translate(glm::mat4(1.0f), getOrigin());

	return t * r * o * s;
}

void Component::Transformable::setComponent(luabridge::LuaRef & table)
{
	using namespace luabridge;
	auto filenameRef = table["filename"];
	if (filenameRef.isTable()) m_vPosition = glm::make_vec3(filenameRef.cast<float*>());
	else std::cout << "Error, Transformable.position is not a table!" << std::endl;
}
