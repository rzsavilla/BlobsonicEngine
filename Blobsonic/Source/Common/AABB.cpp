#include <stdafx.h>
#include "AABB.h"
#include <iostream>


AABB::AABB()
{

}

AABB::AABB(Model model)
{
	m_RenderModel = model;
	//initliaise variables
	m_vPosition = m_RenderModel.getPosition();
	m_vScale = m_RenderModel.getScale();
	m_vCenter = m_vPosition + m_vScale / 2.0f;


}

void AABB::update(const float dt)
{
	m_vCenter = m_vPosition + m_vScale / 2.0f;
	m_RenderModel.setPosition(m_vPosition);
}

void AABB::init()
{
}

void AABB::handleMessage(std::shared_ptr<Message> msg)
{
}

void AABB::setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr)
{
}

void AABB::CollideWithBox(AABB* other)
{

	m_vCenter = m_vPosition + m_vScale / 2.0f;

	//create positions of all vertecies
	obb1LocalPoints[0] = glm::vec3(m_vCenter.x - m_vScale.x / 2, m_vCenter.y + m_vScale.y / 2, m_vCenter.z + m_vScale.z / 2);	//Front - Top left
	obb1LocalPoints[1] = glm::vec3(m_vCenter.x + m_vScale.x / 2, m_vCenter.y + m_vScale.y / 2, m_vCenter.z + m_vScale.z / 2);	//Front - Top Right
	obb1LocalPoints[2] = glm::vec3(m_vCenter.x + m_vScale.x / 2, m_vCenter.y - m_vScale.y / 2, m_vCenter.z + m_vScale.z / 2);	//Front - Bottom Right
	obb1LocalPoints[3] = glm::vec3(m_vCenter.x - m_vScale.x / 2, m_vCenter.y - m_vScale.y / 2, m_vCenter.z + m_vScale.z / 2);	//Front - Bottom left
	obb1LocalPoints[4] = glm::vec3(m_vCenter.x - m_vScale.x / 2, m_vCenter.y + m_vScale.y / 2, m_vCenter.z - m_vScale.z / 2);	//Back - Top left
	obb1LocalPoints[5] = glm::vec3(m_vCenter.x + m_vScale.x / 2, m_vCenter.y + m_vScale.y / 2, m_vCenter.z - m_vScale.z / 2);	//Back - Top Right
	obb1LocalPoints[6] = glm::vec3(m_vCenter.x + m_vScale.x / 2, m_vCenter.y - m_vScale.y / 2, m_vCenter.z - m_vScale.z / 2);	//Back - Bottom Right
	obb1LocalPoints[7] = glm::vec3(m_vCenter.x - m_vScale.x / 2, m_vCenter.y - m_vScale.y / 2, m_vCenter.z - m_vScale.z / 2);	//Back - Bottom left


	obb2LocalPoints[0] = glm::vec3(other->m_vCenter.x - other->m_vScale.x / 2, other->m_vCenter.y + other->m_vScale.y / 2, other->m_vCenter.z + other->m_vScale.z / 2);	//Front - Top left
	obb2LocalPoints[1] = glm::vec3(other->m_vCenter.x + other->m_vScale.x / 2, other->m_vCenter.y + other->m_vScale.y / 2, other->m_vCenter.z + other->m_vScale.z / 2);	//Front - Top Right
	obb2LocalPoints[2] = glm::vec3(other->m_vCenter.x + other->m_vScale.x / 2, other->m_vCenter.y - other->m_vScale.y / 2, other->m_vCenter.z + other->m_vScale.z / 2);	//Front - Bottom Right
	obb2LocalPoints[3] = glm::vec3(other->m_vCenter.x - other->m_vScale.x / 2, other->m_vCenter.y - other->m_vScale.y / 2, other->m_vCenter.z + other->m_vScale.z / 2);	//Front - Bottom left
	obb2LocalPoints[4] = glm::vec3(other->m_vCenter.x - other->m_vScale.x / 2, other->m_vCenter.y + other->m_vScale.y / 2, other->m_vCenter.z - other->m_vScale.z / 2);	//Back - Top left
	obb2LocalPoints[5] = glm::vec3(other->m_vCenter.x + other->m_vScale.x / 2, other->m_vCenter.y + other->m_vScale.y / 2, other->m_vCenter.z - other->m_vScale.z / 2);	//Back - Top Right
	obb2LocalPoints[6] = glm::vec3(other->m_vCenter.x + other->m_vScale.x / 2, other->m_vCenter.y - other->m_vScale.y / 2, other->m_vCenter.z - other->m_vScale.z / 2);	//Back - Bottom Right
	obb2LocalPoints[7] = glm::vec3(other->m_vCenter.x - other->m_vScale.x / 2, other->m_vCenter.y - other->m_vScale.y / 2, other->m_vCenter.z - other->m_vScale.z / 2);	//Back - Bottom left


	//set up the mins and maxs
	m_fMinX = 9999999999999999999.0f;
	m_fMinY = 9999999999999999999.0f;
	m_fMinZ = 9999999999999999999.0f;
		  
	m_fMaxX = -9999999999999999999.0f;
	m_fMaxY = -9999999999999999999.0f;
	m_fMaxZ = -9999999999999999999.0f;

	other->m_fMinX = 9999999999999999999.0f;
	other->m_fMinY = 9999999999999999999.0f;
	other->m_fMinZ = 9999999999999999999.0f;

	other->m_fMaxX = -9999999999999999999.0f;
	other->m_fMaxY = -9999999999999999999.0f;
	other->m_fMaxZ = -9999999999999999999.0f;

	//loop all the axis's for box 1

	for (int i = 0; i < 8; i++)
	{
		if (obb1LocalPoints[i].x < m_fMinX)
		{
			m_fMinX = obb1LocalPoints[i].x;
		}
		if (obb1LocalPoints[i].y < m_fMinY)
		{
			m_fMinY = obb1LocalPoints[i].y;
		}
		if (obb1LocalPoints[i].z < m_fMinZ)
		{
			m_fMinZ = obb1LocalPoints[i].z;
		}
		//max
		if (obb1LocalPoints[i].x > m_fMaxX)
		{
			m_fMaxX = obb1LocalPoints[i].x;
		}
		if (obb1LocalPoints[i].y > m_fMaxY)
		{
			m_fMaxY = obb1LocalPoints[i].y;
		}
		if (obb1LocalPoints[i].z > m_fMaxZ)
		{
			m_fMaxZ = obb1LocalPoints[i].z;
		}
	}
	//loop all the axis's for box 2

	for (int i = 0; i < 8; i++)
	{
		if (obb2LocalPoints[i].x <other->m_fMinX)
		{
			other->m_fMinX = obb2LocalPoints[i].x;
		}
		if (obb2LocalPoints[i].y < other->m_fMinY)
		{
			other->m_fMinY = obb2LocalPoints[i].y;
		}
		if (obb2LocalPoints[i].z < other->m_fMinZ)
		{
			other->m_fMinZ = obb2LocalPoints[i].z;
		}

		//max
		if (obb2LocalPoints[i].x > other->m_fMaxX)
		{
			other->m_fMaxX = obb2LocalPoints[i].x;
		}
		if (obb2LocalPoints[i].y > other->m_fMaxY)
		{
			other->m_fMaxY = obb2LocalPoints[i].y;
		}
		if (obb2LocalPoints[i].z > other->m_fMaxZ)
		{
			other->m_fMaxZ = obb2LocalPoints[i].z;
		}
	}

	//test for an overlap x
	if (m_fMinX <= other->m_fMaxX && m_fMinX >= other->m_fMinX)
	{
		testAxis[0] = true;
	}
	else if (m_fMaxX >= other->m_fMinX && m_fMaxX <= other->m_fMaxX)
	{
		testAxis[0] = true;
	}
	else
	{
		testAxis[0] = false;
		
	}
	//test for an overlap y
	if (m_fMinY <= other->m_fMaxY && m_fMinY >= other->m_fMinY)
	{
		testAxis[1] = true;
	}
	else if (m_fMaxY >= other->m_fMinY && m_fMaxY <= other->m_fMaxY)
	{
		testAxis[1] = true;
	}
	else
	{
		testAxis[1] = false;
	}

	//test for an overlap z
	if (m_fMinZ <= other->m_fMaxZ && m_fMinZ >= other->m_fMinZ)
	{
		testAxis[2] = true;
	}
	else if (m_fMaxZ >= other->m_fMinZ && m_fMaxZ <= other->m_fMaxZ)
	{
		testAxis[2] = true;
	}
	else
	{
		testAxis[2] = false;

	}

	if (testAxis[0] && testAxis[1] && testAxis[2])
	{
		std::cout << " AABB Collision" << std::endl;
	}
	else
	{
		std::cout << "No AABB Collision" << std::endl;
	}
	

}

void AABB::movementForTesting(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

