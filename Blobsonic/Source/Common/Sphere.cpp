#include <stdafx.h>
#include "Sphere.h"
#include <iostream>


Sphere::Sphere()
{

}

Sphere::Sphere(Model model)
{
	m_RenderModel = model;
	//initliaise variables
	m_vPosition = m_RenderModel.getPosition();
	m_vScale = m_RenderModel.getScale();
	m_vCenter = m_vPosition + m_vScale / 2.0f;
	m_fRadius = m_RenderModel.getScale().x;


}

void Sphere::update(const float dt)
{
	m_RenderModel.setPosition(m_vPosition);
}

void Sphere::init()
{
}

void Sphere::handleMessage(std::shared_ptr<Message> msg)
{
}

void Sphere::setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr)
{
}

void Sphere::CollideWithSphere(Sphere* other)
{

	

}

void Sphere::CollideWithOBB(OBB * other)
{
	//find center of OBB
	glm::vec3 center = other->getCenter();

	//find dist between
	m_vCenter = m_vPosition;
	glm::vec3 dist = m_vCenter - center;

	//find clamp
	glm::vec3 clamp;

	//find extends
	glm::vec3 extents = other->getExtents();

	
	//find shortest distnace
	// x - axis
	if (dist.x >= 0) clamp.x = std::min(dist.x, extents.x);
	if (dist.x < 0) clamp.x = std::max(dist.x, -extents.x);

	// y - axis
	if (dist.y >= 0) clamp.y = std::min(dist.y, extents.y);
	if (dist.y < 0) clamp.y = std::max(dist.y, -extents.y);

	// z - axis
	if (dist.z >= 0) clamp.z = std::min(dist.z, extents.z);
	if (dist.z < 0) clamp.z = std::max(dist.z, -extents.z);

	//find the distance from the edge of the box to the centere of the sphere
	glm::vec3 diff = m_vCenter - clamp;

	//find the distance from the edge of the box to the edge of the sphere
	float distance = sqrt((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z)) - m_fRadius;

	if (distance > 0) std::cout << "No Collision" << std::endl;
	else if(distance <= 0)std::cout << "Collision" << std::endl;

	//std::cout << "Sphere : " << m_vCenter.x << " " << m_vCenter.y << " " << m_vCenter.z << " OBB : " << center.x << " " << center.y << " " << center.z << std::endl;
	std::cout << clamp.x << " " << clamp.y << " " << clamp.z << std::endl;
	//std::cout << m_fRadius << std::endl;

}

void Sphere::movementForTesting(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

