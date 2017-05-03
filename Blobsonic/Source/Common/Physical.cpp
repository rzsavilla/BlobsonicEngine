#include <stdafx.h>
#include "Physical.h"

Physical::Physical()
{
	m_fMass = 1;
	m_fINVMass = 1 / m_fMass;
	m_vAcceleration = glm::vec3(0, 0, 0);
	m_vVelocity = glm::vec3(0, 0, 0);
	m_fRestitution = 0.1f;
}

void Physical::setMass(float newMass)
{
	m_fMass = newMass;
}

void Physical::setRestitution(float newRestitution)
{
	m_fINVMass = newRestitution;
}

float Physical::getMass()
{
	return m_fMass;
}

float Physical::getRestitition()
{
	return m_fRestitution;
}
