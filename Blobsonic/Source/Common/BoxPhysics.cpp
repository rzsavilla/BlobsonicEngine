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
	m_vPosition = glm::vec3(1.0f, 20.0f, 1.0f);
	m_fMass = 10;
	m_fForce = glm::vec3(0.0f, 0.0f, 0.0f);
	m_fVelocity = glm::vec3(0.0f, 00.0f, 0.0f);
	m_vAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

void BoxPhysics::update(const float dt)
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
	
	std::cout << "Update physics box : " << m_vPosition.x << " " << m_vPosition.y << " " << m_vPosition.z << std::endl;

	m_RenderModel.setPosition(m_vPosition);

}

