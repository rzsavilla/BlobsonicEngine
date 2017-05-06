#include <stdafx.h>
#include "Physical.h"

Physical::Physical()
{
	m_fMass = 1;
	m_fINVMass = 1 / m_fMass;
	m_vAcceleration = glm::vec3(0, 0, 0);
	m_vVelocity = glm::vec3(0, 0, 0);
	m_fRestitution = 0.1f;

	m_bEnableGravitiy = true;
}

void Physical::setMass(float newMass)
{
	m_fMass = newMass;
}

void Physical::setfINVMass(float newINVMass)
{
	m_fINVMass = newINVMass;
}

void Physical::setRestitution(float newRestitution)
{
	m_fINVMass = newRestitution;
}

void Physical::setForce(glm::vec3 newFoce)
{
	m_fForce = newFoce;
}

void Physical::applyForce(glm::vec3 appliedForce)
{
	m_fForce += appliedForce;
}

void Physical::setVelocity(glm::vec3 velocity)
{
	m_vVelocity = velocity;
}

float Physical::getMass()
{
	return m_fMass;
}

float Physical::getINVMass()
{
	return m_fINVMass;
}

float Physical::getRestitition()
{
	return m_fRestitution;
}

glm::vec3 Physical::getForce()
{
	return m_fForce;
}

glm::vec3 Physical::getVelocity()
{
	return m_vVelocity;
}

glm::vec3 Physical::getAcceleration()
{
	glm::vec3 accel(m_vAcceleration.x, m_vAcceleration.y - 9.81, m_vAcceleration.z);
	return accel;
}

void Physical::applyImpulse(glm::vec3 Normal, float force)
{
	float Acceleration = force / m_fMass;

	//multiply normal my accerlation
	m_vAcceleration = Normal * Acceleration;
}
