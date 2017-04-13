#include "stdafx.h"
#include "Physics.h"
#include "AABB.h"


System::Physics::Physics()
{

}

void System::Physics::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	m_vAABBS.clear();

	for (auto it = entities->begin(); it != entities->end(); ++it)
	{
		if ((*it)->has<AABB>() && (*it)->has<Component::Transformable>()) {
			m_vAABBS.push_back((*it));

		}
	}

}

void System::Physics::update(float dt)
{
	//process AABB
	for (int i = 0; i < m_vAABBS.size(); i++)
	{
		for (int x = 0; x < m_vAABBS.size(); x++)
		{
			if (i != x)
			{
				CheckAABBAABBCollision(m_vAABBS.at(i), m_vAABBS.at(x));
			}
		}

	}



}

void System::Physics::processMessages(const std::vector<std::shared_ptr<Message>>* msgs)
{

}

bool System::Physics::CheckAABBAABBCollision(std::shared_ptr<Entity> aabb1, std::shared_ptr<Entity> aabb2)
{
	
	auto aabox1 = aabb1->get<AABB>();
	auto aabox2 = aabb2->get<AABB>();

	auto box1 = aabb1->get<Component::Transformable>();
	auto box2 = aabb2->get<Component::Transformable>();

	box1->m_vCenter = box1->m_vPosition + box1->m_vDimensions / 2.0f;
	box2->m_vCenter = box2->m_vPosition + box2->m_vDimensions / 2.0f;

	//create positions of all vertecies
	aabox1->obbLocalPoints[0] = glm::vec3(box1->m_vCenter.x - box1->m_vDimensions.x / 2, box1->m_vCenter.y + box1->m_vDimensions.y / 2, box1->m_vCenter.z + box1->m_vDimensions.z / 2);	//Front - Top left
	aabox1->obbLocalPoints[1] = glm::vec3(box1->m_vCenter.x + box1->m_vDimensions.x / 2, box1->m_vCenter.y + box1->m_vDimensions.y / 2, box1->m_vCenter.z + box1->m_vDimensions.z / 2);	//Front - Top Right
	aabox1->obbLocalPoints[2] = glm::vec3(box1->m_vCenter.x + box1->m_vDimensions.x / 2, box1->m_vCenter.y - box1->m_vDimensions.y / 2, box1->m_vCenter.z + box1->m_vDimensions.z / 2);	//Front - Bottom Right
	aabox1->obbLocalPoints[3] = glm::vec3(box1->m_vCenter.x - box1->m_vDimensions.x / 2, box1->m_vCenter.y - box1->m_vDimensions.y / 2, box1->m_vCenter.z + box1->m_vDimensions.z / 2);	//Front - Bottom left
	aabox1->obbLocalPoints[4] = glm::vec3(box1->m_vCenter.x - box1->m_vDimensions.x / 2, box1->m_vCenter.y + box1->m_vDimensions.y / 2, box1->m_vCenter.z - box1->m_vDimensions.z / 2);	//Back - Top left
	aabox1->obbLocalPoints[5] = glm::vec3(box1->m_vCenter.x + box1->m_vDimensions.x / 2, box1->m_vCenter.y + box1->m_vDimensions.y / 2, box1->m_vCenter.z - box1->m_vDimensions.z / 2);	//Back - Top Right
	aabox1->obbLocalPoints[6] = glm::vec3(box1->m_vCenter.x + box1->m_vDimensions.x / 2, box1->m_vCenter.y - box1->m_vDimensions.y / 2, box1->m_vCenter.z - box1->m_vDimensions.z / 2);	//Back - Bottom Right
	aabox1->obbLocalPoints[7] = glm::vec3(box1->m_vCenter.x - box1->m_vDimensions.x / 2, box1->m_vCenter.y - box1->m_vDimensions.y / 2, box1->m_vCenter.z - box1->m_vDimensions.z / 2);	//Back - Bottom left
																								 

	aabox2->obbLocalPoints[0] = glm::vec3(box2->m_vCenter.x - box2->m_vDimensions.x / 2, box2->m_vCenter.y + box2->m_vDimensions.y / 2, box2->m_vCenter.z + box2->m_vDimensions.z / 2);	//Front - Top left
	aabox2->obbLocalPoints[1] = glm::vec3(box2->m_vCenter.x + box2->m_vDimensions.x / 2, box2->m_vCenter.y + box2->m_vDimensions.y / 2, box2->m_vCenter.z + box2->m_vDimensions.z / 2);	//Front - Top Right
	aabox2->obbLocalPoints[2] = glm::vec3(box2->m_vCenter.x + box2->m_vDimensions.x / 2, box2->m_vCenter.y - box2->m_vDimensions.y / 2, box2->m_vCenter.z + box2->m_vDimensions.z / 2);	//Front - Bottom Right
	aabox2->obbLocalPoints[3] = glm::vec3(box2->m_vCenter.x - box2->m_vDimensions.x / 2, box2->m_vCenter.y - box2->m_vDimensions.y / 2, box2->m_vCenter.z + box2->m_vDimensions.z / 2);	//Front - Bottom left
	aabox2->obbLocalPoints[4] = glm::vec3(box2->m_vCenter.x - box2->m_vDimensions.x / 2, box2->m_vCenter.y + box2->m_vDimensions.y / 2, box2->m_vCenter.z - box2->m_vDimensions.z / 2);	//Back - Top left
	aabox2->obbLocalPoints[5] = glm::vec3(box2->m_vCenter.x + box2->m_vDimensions.x / 2, box2->m_vCenter.y + box2->m_vDimensions.y / 2, box2->m_vCenter.z - box2->m_vDimensions.z / 2);	//Back - Top Right
	aabox2->obbLocalPoints[6] = glm::vec3(box2->m_vCenter.x + box2->m_vDimensions.x / 2, box2->m_vCenter.y - box2->m_vDimensions.y / 2, box2->m_vCenter.z - box2->m_vDimensions.z / 2);	//Back - Bottom Right
	aabox2->obbLocalPoints[7] = glm::vec3(box2->m_vCenter.x - box2->m_vDimensions.x / 2, box2->m_vCenter.y - box2->m_vDimensions.y / 2, box2->m_vCenter.z - box2->m_vDimensions.z / 2);	//Back - Bottom left


	//set up the mins and maxs
	aabox1->m_fMinX = 9999999999999999999.0f;
	aabox1->m_fMinY = 9999999999999999999.0f;
	aabox1->m_fMinZ = 9999999999999999999.0f;

	aabox1->m_fMaxX = -9999999999999999999.0f;
	aabox1->m_fMaxY = -9999999999999999999.0f;
	aabox1->m_fMaxZ = -9999999999999999999.0f;

	aabox2->m_fMinX = 9999999999999999999.0f;
	aabox2->m_fMinY = 9999999999999999999.0f;
	aabox2->m_fMinZ = 9999999999999999999.0f;

	aabox2->m_fMaxX = -9999999999999999999.0f;
	aabox2->m_fMaxY = -9999999999999999999.0f;
	aabox2->m_fMaxZ = -9999999999999999999.0f;

	//loop all the axis's for box 1

	for (int i = 0; i < 8; i++)
	{
		if (aabox1->obbLocalPoints[i].x < aabox1->m_fMinX)
		{
			aabox1->m_fMinX = aabox1->obbLocalPoints[i].x;
		}
		if (aabox1->obbLocalPoints[i].y < aabox1->m_fMinY)
		{
			aabox1->m_fMinY = aabox1->obbLocalPoints[i].y;
		}
		if (aabox1->obbLocalPoints[i].z < aabox1->m_fMinZ)
		{
			aabox1->m_fMinZ = aabox1->obbLocalPoints[i].z;
		}
		//max
		if (aabox1->obbLocalPoints[i].x > aabox1->m_fMaxX)
		{
			aabox1->m_fMaxX = aabox1->obbLocalPoints[i].x;
		}
		if (aabox1->obbLocalPoints[i].y > aabox1->m_fMaxY)
		{
			aabox1->m_fMaxY = aabox1->obbLocalPoints[i].y;
		}
		if (aabox1->obbLocalPoints[i].z > aabox1->m_fMaxZ)
		{
			aabox1->m_fMaxZ = aabox1->obbLocalPoints[i].z;
		}
	}
	//loop all the axis's for box 2

	for (int i = 0; i < 8; i++)
	{
		if (aabox2->obbLocalPoints[i].x < aabox2->m_fMinX)
		{
			aabox2->m_fMinX = aabox2->obbLocalPoints[i].x;
		}
		if (aabox2->obbLocalPoints[i].y < aabox2->m_fMinY)
		{
			aabox2->m_fMinY = aabox2->obbLocalPoints[i].y;
		}
		if (aabox2->obbLocalPoints[i].z < aabox2->m_fMinZ)
		{
			aabox2->m_fMinZ = aabox2->obbLocalPoints[i].z;
		}

		//max
		if (aabox2->obbLocalPoints[i].x > aabox2->m_fMaxX)
		{
			aabox2->m_fMaxX = aabox2->obbLocalPoints[i].x;
		}
		if (aabox2->obbLocalPoints[i].y > aabox2->m_fMaxY)
		{
			aabox2->m_fMaxY = aabox2->obbLocalPoints[i].y;
		}
		if (aabox2->obbLocalPoints[i].z > aabox2->m_fMaxZ)
		{
			aabox2->m_fMaxZ = aabox2->obbLocalPoints[i].z;
		}
	}

	//test for an overlap x
	if (aabox1->m_fMinX <= aabox2->m_fMaxX && aabox1->m_fMinX >= aabox2->m_fMinX)
	{
		aabox1->testAxis[0] = true;
	}
	else if (aabox1->m_fMaxX >= aabox2->m_fMinX && aabox1->m_fMaxX <= aabox2->m_fMaxX)
	{
		aabox1->testAxis[0] = true;
	}
	else
	{
		aabox1->testAxis[0] = false;

	}
	//test for an overlap y
	if (aabox1->m_fMinY <= aabox2->m_fMaxY && aabox1->m_fMinY >= aabox2->m_fMinY)
	{
		aabox1->testAxis[1] = true;
	}
	else if (aabox1->m_fMaxY >= aabox2->m_fMinY && aabox1->m_fMaxY <= aabox2->m_fMaxY)
	{
		aabox1->testAxis[1] = true;
	}
	else
	{
		aabox1->testAxis[1] = false;
	}

	//test for an overlap z
	if (aabox1->m_fMinZ <= aabox2->m_fMaxZ && aabox1->m_fMinZ >= aabox2->m_fMinZ)
	{
		aabox1->testAxis[2] = true;
	}
	else if (aabox1->m_fMaxZ >= aabox2->m_fMinZ && aabox1->m_fMaxZ <= aabox2->m_fMaxZ)
	{
		aabox1->testAxis[2] = true;
	}
	else
	{
		aabox1->testAxis[2] = false;

	}

	if (aabox1->testAxis[0] && aabox1->testAxis[1] && aabox1->testAxis[2])
	{
		std::cout << " AABB Collision" << std::endl;
		return true;
	}
	else
	{
		std::cout << "No AABB Collision" << std::endl;
		return false;
	}


}
