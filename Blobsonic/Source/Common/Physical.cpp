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
