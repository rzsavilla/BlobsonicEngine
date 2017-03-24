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
	m_vCenter = m_vPosition;
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
	//find the dist between the centre of each sphere
	glm::vec3 Dist = m_vCenter - other->getCenter();

	//find the magnitude of this distance
	float magDist = sqrt((Dist.x * Dist.x) + (Dist.y * Dist.y) + (Dist.z * Dist.z));
	
	//subtract the radius 
	magDist  = magDist - m_fRadius;

	if (magDist <= other->getRadius()) std::cout << "Collision" << std::endl;
	else  std::cout << "No Collision" << std::endl;

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


	//multiply the clmap by the rotation matrix
	//clamp = clamp  * other->getRotationMatrix();

	//find the distance from the edge of the box to the centere of the sphere
	glm::vec3 diff = dist - clamp;

	//find the distance from the edge of the box to the edge of the sphere
	float distance = sqrt((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z)) - m_fRadius;

	if (distance > 0) std::cout << "No Collision" << std::endl;
	else if(distance <= 0)std::cout << "Collision" << std::endl;

}

void Sphere::movementForTesting(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

float Sphere::getRadius()
{
	return m_fRadius;
}

