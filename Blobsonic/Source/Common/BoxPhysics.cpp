#include <stdafx.h>
#include "BoxPhysics.h"
#include <iostream>


BoxPhysics::BoxPhysics()
{
	//initliaise variables
	m_vPosition = glm::vec3(1.0f, 20.0f, 1.0f);
	m_fMass = 10; 
	m_fForce = glm::vec3(0.0f, 0.0f, 0.0f);
	m_fVelocity = glm::vec3(0.0f, 00.0f, 0.0f);
	m_vAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);


}

BoxPhysics::BoxPhysics(Model model)
{
	m_RenderModel = model;
	//initliaise variables
	m_vPosition = m_RenderModel.getPosition();
	m_vScale = m_RenderModel.getScale();
	m_fMass = 10;
	m_fForce = glm::vec3(0.0f, 0.0f, 0.0f);
	m_fVelocity = glm::vec3(0.0f, 00.0f, 0.0f);
	m_vAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);

}

void BoxPhysics::update(const float dt)
{

	//m_vAcceleration.y = GRAVITYCOEFFICENT;

	////suvat for falling
	//glm::vec3 s = m_vPosition;
	//glm::vec3 u = m_fVelocity;
	//glm::vec3 v = vec3(0,0,0);
	//glm::vec3 a = m_vAcceleration;
	//
	////eular calculation
	//v = u + a * dt;
	//glm::vec3 s2 = s + u * dt;

	////update position
	//m_vPosition = s2;
	//m_fVelocity = v;
	//
	//std::cout << "Update physics box : " << m_vPosition.y << " " << m_fVelocity.y << " " << m_vPosition.y << std::endl;

	m_RenderModel.setPosition(m_vPosition);

}

void BoxPhysics::init()
{
}

void BoxPhysics::handleMessage(std::shared_ptr<Message> msg)
{
}

void BoxPhysics::setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr)
{
}

void BoxPhysics::CollideWithBox(BoxPhysics* other)
{
	
	//setup data for the OBB's
	m_vCenter = m_vPosition;
	m_vExtends = m_vScale / 2.0f;

	other->m_vCenter = other->m_vPosition;
	other->m_vExtends = other->m_vScale / 2.0f;

	//perform an early out check 
	glm::vec3 earlyOutDist(m_vCenter - other->m_vCenter); // distance between center of 2 boxs 
	float magEarlyDist = sqrt(((earlyOutDist.x * earlyOutDist.x) + (earlyOutDist.y * earlyOutDist.y) + (earlyOutDist.z * earlyOutDist.z))); // get magnitude of dist
	float roughSize = m_vExtends.x + m_vExtends.y + m_vExtends.z; // create a rough size from the scale of the box
	std::cout <<"Rough Size : " << roughSize << " magEarlyDist : " << magEarlyDist << std::endl;
	if (magEarlyDist > roughSize * 10.0f) // if further than 10 times the rouch size of the box away
	{
		
		return; // escape collision test before any intensive testing begins
	}
	else
	{












	}

}

void BoxPhysics::movementForTesting(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

