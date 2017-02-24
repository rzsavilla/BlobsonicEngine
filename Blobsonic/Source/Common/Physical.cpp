#include <stdafx.h>
#include "Physical.h"

void Physical::update(float dt)
{
	m_vAcceleration.y = GRAVITYCOEFFICENT;

	//suvat for falling
	glm::vec3 s = m_vPosition;
	glm::vec3 u = m_fVelocity;
	glm::vec3 v = vec3(0,0,0);
	glm::vec3 a = m_vAcceleration;
	
	//eular calculation
	v = u + a * dt;
	glm::vec3 s2 = s + u * dt;

	//update position
	m_vPosition = s2;
	m_fVelocity = v;
	m_vCenter = m_vPosition + m_vScale / 2.0f;
}

void Physical::init()
{
}

void Physical::handleMessage(std::shared_ptr<Message> msg)
{
}

void Physical::setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr)
{
}
