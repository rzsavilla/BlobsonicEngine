#include "stdafx.h"
#include "Physics.h"
#include "AABB.h"
#include "OBB.h"
#include "Sphere.h"

System::Physics::Physics()
{

}

void System::Physics::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	m_vAABBS.clear();
	m_vOBBS.clear();
	m_vSpheres.clear();

	for (auto it = entities->begin(); it != entities->end(); ++it)
	{
		if ((*it)->has<AABB>() && (*it)->has<Component::Transformable>()) {
			m_vAABBS.push_back((*it));

		}
	}

	for (auto it = entities->begin(); it != entities->end(); ++it)
	{
		if ((*it)->has<OBB>() && (*it)->has<Component::Transformable>()) {
			m_vOBBS.push_back((*it));

		}
	}
	for (auto it = entities->begin(); it != entities->end(); ++it)
	{
		if ((*it)->has<Sphere>() && (*it)->has<Component::Transformable>()) {
			m_vSpheres.push_back((*it));

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
	//process OBB
	for (int i = 0; i < m_vOBBS.size(); i++)
	{
		updateOBB(m_vOBBS.at(i));
	}
	for (int i = 0; i < m_vOBBS.size(); i++)
	{
		for (int x = 0; x < m_vOBBS.size(); x++)
		{
			if (i != x)
			{
				CheckOBBOBBCollision(m_vOBBS.at(i), m_vOBBS.at(x));
			}
		}

	}

	//process Sphere
	for (int i = 0; i < m_vSpheres.size(); i++)
	{
		for (int x = 0; x < m_vSpheres.size(); x++)
		{
			if (i != x)
			{
				CheckShereSphereCollision(m_vSpheres.at(i), m_vSpheres.at(x));
			}
		}

	}

	//process Sphere Box Collision
	for (int i = 0; i < m_vSpheres.size(); i++)
	{
		for (int x = 0; x < m_vOBBS.size(); x++)
		{
			
			CheckOBBSphereCollision(m_vOBBS.at(x), m_vSpheres.at(i));
			
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

	aabox1->m_vCenter = box1->m_vPosition + aabox1->m_vDimensions / 2.0f;
	aabox2->m_vCenter = box2->m_vPosition + aabox2->m_vDimensions / 2.0f;

	//create positions of all vertecies
	aabox1->obbLocalPoints[0] = glm::vec3(aabox1->m_vCenter.x - aabox1->m_vDimensions.x / 2, aabox1->m_vCenter.y + aabox1->m_vDimensions.y / 2, aabox1->m_vCenter.z + aabox1->m_vDimensions.z / 2);	//Front - Top left
	aabox1->obbLocalPoints[1] = glm::vec3(aabox1->m_vCenter.x + aabox1->m_vDimensions.x / 2, aabox1->m_vCenter.y + aabox1->m_vDimensions.y / 2, aabox1->m_vCenter.z + aabox1->m_vDimensions.z / 2);	//Front - Top Right
	aabox1->obbLocalPoints[2] = glm::vec3(aabox1->m_vCenter.x + aabox1->m_vDimensions.x / 2, aabox1->m_vCenter.y - aabox1->m_vDimensions.y / 2, aabox1->m_vCenter.z + aabox1->m_vDimensions.z / 2);	//Front - Bottom Right
	aabox1->obbLocalPoints[3] = glm::vec3(aabox1->m_vCenter.x - aabox1->m_vDimensions.x / 2, aabox1->m_vCenter.y - aabox1->m_vDimensions.y / 2, aabox1->m_vCenter.z + aabox1->m_vDimensions.z / 2);	//Front - Bottom left
	aabox1->obbLocalPoints[4] = glm::vec3(aabox1->m_vCenter.x - aabox1->m_vDimensions.x / 2, aabox1->m_vCenter.y + aabox1->m_vDimensions.y / 2, aabox1->m_vCenter.z - aabox1->m_vDimensions.z / 2);	//Back - Top left
	aabox1->obbLocalPoints[5] = glm::vec3(aabox1->m_vCenter.x + aabox1->m_vDimensions.x / 2, aabox1->m_vCenter.y + aabox1->m_vDimensions.y / 2, aabox1->m_vCenter.z - aabox1->m_vDimensions.z / 2);	//Back - Top Right
	aabox1->obbLocalPoints[6] = glm::vec3(aabox1->m_vCenter.x + aabox1->m_vDimensions.x / 2, aabox1->m_vCenter.y - aabox1->m_vDimensions.y / 2, aabox1->m_vCenter.z - aabox1->m_vDimensions.z / 2);	//Back - Bottom Right
	aabox1->obbLocalPoints[7] = glm::vec3(aabox1->m_vCenter.x - aabox1->m_vDimensions.x / 2, aabox1->m_vCenter.y - aabox1->m_vDimensions.y / 2, aabox1->m_vCenter.z - aabox1->m_vDimensions.z / 2);	//Back - Bottom left
																								 												
																																				
	aabox2->obbLocalPoints[0] = glm::vec3(aabox2->m_vCenter.x - aabox2->m_vDimensions.x / 2, aabox2->m_vCenter.y + aabox2->m_vDimensions.y / 2, aabox2->m_vCenter.z + aabox2->m_vDimensions.z / 2);	//Front - Top left
	aabox2->obbLocalPoints[1] = glm::vec3(aabox2->m_vCenter.x + aabox2->m_vDimensions.x / 2, aabox2->m_vCenter.y + aabox2->m_vDimensions.y / 2, aabox2->m_vCenter.z + aabox2->m_vDimensions.z / 2);	//Front - Top Right
	aabox2->obbLocalPoints[2] = glm::vec3(aabox2->m_vCenter.x + aabox2->m_vDimensions.x / 2, aabox2->m_vCenter.y - aabox2->m_vDimensions.y / 2, aabox2->m_vCenter.z + aabox2->m_vDimensions.z / 2);	//Front - Bottom Right
	aabox2->obbLocalPoints[3] = glm::vec3(aabox2->m_vCenter.x - aabox2->m_vDimensions.x / 2, aabox2->m_vCenter.y - aabox2->m_vDimensions.y / 2, aabox2->m_vCenter.z + aabox2->m_vDimensions.z / 2);	//Front - Bottom left
	aabox2->obbLocalPoints[4] = glm::vec3(aabox2->m_vCenter.x - aabox2->m_vDimensions.x / 2, aabox2->m_vCenter.y + aabox2->m_vDimensions.y / 2, aabox2->m_vCenter.z - aabox2->m_vDimensions.z / 2);	//Back - Top left
	aabox2->obbLocalPoints[5] = glm::vec3(aabox2->m_vCenter.x + aabox2->m_vDimensions.x / 2, aabox2->m_vCenter.y + aabox2->m_vDimensions.y / 2, aabox2->m_vCenter.z - aabox2->m_vDimensions.z / 2);	//Back - Top Right
	aabox2->obbLocalPoints[6] = glm::vec3(aabox2->m_vCenter.x + aabox2->m_vDimensions.x / 2, aabox2->m_vCenter.y - aabox2->m_vDimensions.y / 2, aabox2->m_vCenter.z - aabox2->m_vDimensions.z / 2);	//Back - Bottom Right
	aabox2->obbLocalPoints[7] = glm::vec3(aabox2->m_vCenter.x - aabox2->m_vDimensions.x / 2, aabox2->m_vCenter.y - aabox2->m_vDimensions.y / 2, aabox2->m_vCenter.z - aabox2->m_vDimensions.z / 2);	//Back - Bottom left
																

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
		return true;
	}
	else
	{
		return false;
	}


}

bool System::Physics::CheckOBBOBBCollision(std::shared_ptr<Entity> obb1, std::shared_ptr<Entity> obb2)
{

	//setup data for the OBB's
	auto obox1 = obb1->get<OBB>();
	auto obox2 = obb2->get<OBB>();

	auto box1 = obb1->get<Component::Transformable>();
	auto box2 = obb2->get<Component::Transformable>();

	bool testAxis[6];


	// begin collison check!!!!

	//create local versions

	

	//create positions of all vertecies
	obox1->m_obbLocalPoints[0] = glm::vec3(obox1->m_vCenter.x - obox1->m_vDimensions.x / 2, obox1->m_vCenter.y + obox1->m_vDimensions.y / 2, obox1->m_vCenter.z + obox1->m_vDimensions.z / 2);	//Front - Top left
	obox1->m_obbLocalPoints[1] = glm::vec3(obox1->m_vCenter.x + obox1->m_vDimensions.x / 2, obox1->m_vCenter.y + obox1->m_vDimensions.y / 2, obox1->m_vCenter.z + obox1->m_vDimensions.z / 2);	//Front - Top Right
	obox1->m_obbLocalPoints[2] = glm::vec3(obox1->m_vCenter.x + obox1->m_vDimensions.x / 2, obox1->m_vCenter.y - obox1->m_vDimensions.y / 2, obox1->m_vCenter.z + obox1->m_vDimensions.z / 2);	//Front - Bottom Right
	obox1->m_obbLocalPoints[3] = glm::vec3(obox1->m_vCenter.x - obox1->m_vDimensions.x / 2, obox1->m_vCenter.y - obox1->m_vDimensions.y / 2, obox1->m_vCenter.z + obox1->m_vDimensions.z / 2);	//Front - Bottom left
	obox1->m_obbLocalPoints[4] = glm::vec3(obox1->m_vCenter.x - obox1->m_vDimensions.x / 2, obox1->m_vCenter.y + obox1->m_vDimensions.y / 2, obox1->m_vCenter.z - obox1->m_vDimensions.z / 2);	//Back - Top left
	obox1->m_obbLocalPoints[5] = glm::vec3(obox1->m_vCenter.x + obox1->m_vDimensions.x / 2, obox1->m_vCenter.y + obox1->m_vDimensions.y / 2, obox1->m_vCenter.z - obox1->m_vDimensions.z / 2);	//Back - Top Right
	obox1->m_obbLocalPoints[6] = glm::vec3(obox1->m_vCenter.x + obox1->m_vDimensions.x / 2, obox1->m_vCenter.y - obox1->m_vDimensions.y / 2, obox1->m_vCenter.z - obox1->m_vDimensions.z / 2);	//Back - Bottom Right
	obox1->m_obbLocalPoints[7] = glm::vec3(obox1->m_vCenter.x - obox1->m_vDimensions.x / 2, obox1->m_vCenter.y - obox1->m_vDimensions.y / 2, obox1->m_vCenter.z - obox1->m_vDimensions.z / 2);	//Back - Bottom left


	obox2->m_obbLocalPoints[0] = glm::vec3(obox2->m_vCenter.x - obox2->m_vDimensions.x / 2, obox2->m_vCenter.y + obox2->m_vDimensions.y / 2,obox2->m_vCenter.z + obox2->m_vDimensions.z / 2);	//Front - Top left
	obox2->m_obbLocalPoints[1] = glm::vec3(obox2->m_vCenter.x + obox2->m_vDimensions.x / 2, obox2->m_vCenter.y + obox2->m_vDimensions.y / 2,obox2->m_vCenter.z + obox2->m_vDimensions.z / 2);	//Front - Top Right
	obox2->m_obbLocalPoints[2] = glm::vec3(obox2->m_vCenter.x + obox2->m_vDimensions.x / 2, obox2->m_vCenter.y - obox2->m_vDimensions.y / 2,obox2->m_vCenter.z + obox2->m_vDimensions.z / 2);	//Front - Bottom Right
	obox2->m_obbLocalPoints[3] = glm::vec3(obox2->m_vCenter.x - obox2->m_vDimensions.x / 2, obox2->m_vCenter.y - obox2->m_vDimensions.y / 2,obox2->m_vCenter.z + obox2->m_vDimensions.z / 2);	//Front - Bottom left
	obox2->m_obbLocalPoints[4] = glm::vec3(obox2->m_vCenter.x - obox2->m_vDimensions.x / 2, obox2->m_vCenter.y + obox2->m_vDimensions.y / 2,obox2->m_vCenter.z - obox2->m_vDimensions.z / 2);	//Back - Top left
	obox2->m_obbLocalPoints[5] = glm::vec3(obox2->m_vCenter.x + obox2->m_vDimensions.x / 2, obox2->m_vCenter.y + obox2->m_vDimensions.y / 2,obox2->m_vCenter.z - obox2->m_vDimensions.z / 2);	//Back - Top Right
	obox2->m_obbLocalPoints[6] = glm::vec3(obox2->m_vCenter.x + obox2->m_vDimensions.x / 2, obox2->m_vCenter.y - obox2->m_vDimensions.y / 2,obox2->m_vCenter.z - obox2->m_vDimensions.z / 2);	//Back - Bottom Right
	obox2->m_obbLocalPoints[7] = glm::vec3(obox2->m_vCenter.x - obox2->m_vDimensions.x / 2, obox2->m_vCenter.y - obox2->m_vDimensions.y / 2,obox2->m_vCenter.z - obox2->m_vDimensions.z / 2);	//Back - Bottom left

	//multiply points by rotation matrix			

	
	obox1->m_Rotation = glm::rotate(obox1->m_Rotation, box1->getRotation().x, glm::vec3(1.0f, 0.0, 0.0f));
	obox1->m_Rotation = glm::rotate(obox1->m_Rotation, box1->getRotation().y, glm::vec3(0.0f, 1.0, 0.0f));
	obox1->m_Rotation = glm::rotate(obox1->m_Rotation, box1->getRotation().z, glm::vec3(0.0f, 0.0, 1.0f));

	obox1->m_obbLocalPoints[0] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[0];
	obox1->m_obbLocalPoints[1] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[1];
	obox1->m_obbLocalPoints[2] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[2];
	obox1->m_obbLocalPoints[3] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[3];
	obox1->m_obbLocalPoints[4] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[4];
	obox1->m_obbLocalPoints[5] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[5];
	obox1->m_obbLocalPoints[6] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[6];
	obox1->m_obbLocalPoints[7] = glm::mat3(obox1->m_Rotation)  * obox1->m_obbLocalPoints[7];


	obox2->m_Rotation = glm::rotate(obox2->m_Rotation, box2->getRotation().x, glm::vec3(1.0f, 0.0, 0.0f));
	obox2->m_Rotation = glm::rotate(obox2->m_Rotation, box2->getRotation().y, glm::vec3(0.0f, 1.0, 0.0f));
	obox2->m_Rotation = glm::rotate(obox2->m_Rotation, box2->getRotation().z, glm::vec3(0.0f, 0.0, 1.0f));
	
	obox2->m_obbLocalPoints[0] = obox2->m_obbLocalPoints[0] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[1] = obox2->m_obbLocalPoints[1] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[2] = obox2->m_obbLocalPoints[2] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[3] = obox2->m_obbLocalPoints[3] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[4] = obox2->m_obbLocalPoints[4] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[5] = obox2->m_obbLocalPoints[5] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[6] = obox2->m_obbLocalPoints[6] * glm::mat3(obox2->m_Rotation);
	obox2->m_obbLocalPoints[7] = obox2->m_obbLocalPoints[7] * glm::mat3(obox2->m_Rotation);

	//create normals for each face
	obox1->m_obbNormals[0] = glm::mat3(obox1->m_Rotation) * glm::vec3(0, 0, 1);  // front face
	obox1->m_obbNormals[1] = glm::mat3(obox1->m_Rotation) * glm::vec3(0, 0, -1); // back face
	obox1->m_obbNormals[2] = glm::mat3(obox1->m_Rotation) * glm::vec3(-1, 0, 0); // left face
	obox1->m_obbNormals[3] = glm::mat3(obox1->m_Rotation) * glm::vec3(1, 0, 0); // right face
	obox1->m_obbNormals[4] = glm::mat3(obox1->m_Rotation) * glm::vec3(0, 1, 0); // Top face
	obox1->m_obbNormals[5] = glm::mat3(obox1->m_Rotation) * glm::vec3(0, -1, 0); // bottom face

	obox2->m_obbNormals[0] = glm::mat3(obox2->m_Rotation) * glm::vec3(0, 0, 1);  // front face
	obox2->m_obbNormals[1] = glm::mat3(obox2->m_Rotation) * glm::vec3(0, 0, -1); // back face
	obox2->m_obbNormals[2] = glm::mat3(obox2->m_Rotation) * glm::vec3(-1, 0, 0); // left face
	obox2->m_obbNormals[3] = glm::mat3(obox2->m_Rotation) * glm::vec3(1, 0, 0); // right face
	obox2->m_obbNormals[4] = glm::mat3(obox2->m_Rotation) * glm::vec3(0, 1, 0); // Top face
	obox2->m_obbNormals[5] = glm::mat3(obox2->m_Rotation) * glm::vec3(0, -1, 0); // bottom face



																	//project 6 axis 
	for (int axisTest = 0; axisTest < 6; axisTest++)
	{
		//values for min box2->and max
		float obb1Min = 999999999999999999999.0f;
		float obb1Max = -999999999999999999999.0f;
		float obb2Min = 999999999999999999999.0f;
		float obb2Max = -999999999999999999999.0f;


		// check all vertecies on box 1
		for (int box1Vertex = 0; box1Vertex < 8; box1Vertex++)
		{
			float fDotProduct = glm::dot(obox1->m_obbNormals[axisTest], obox1->m_obbLocalPoints[box1Vertex]);
			if (fDotProduct < obb1Min)
			{
				obb1Min = fDotProduct;
			}
			if (fDotProduct > obb1Max)
			{
				obb1Max = fDotProduct;
			}

		}

		// check all vertecies on box 2
		for (int box2Vertex = 0; box2Vertex < 8; box2Vertex++)
		{
			float fDotProduct = glm::dot(obox1->m_obbNormals[axisTest], obox2->m_obbLocalPoints[box2Vertex]);
			if (fDotProduct < obb2Min)
			{
				obb2Min = fDotProduct;
			}
			if (fDotProduct > obb2Max)
			{
				obb2Max = fDotProduct;
			}

		}

		//check each box min and max for over lap
		if (obb2Min <= obb1Max && obb2Min >= obb1Min)
		{
			testAxis[axisTest] = true; // There is a collision along this axis
		}
		else if (obb2Max >= obb1Min && obb2Max <= obb1Max)
		{
			testAxis[axisTest] = true; // There is a collision along this axis
		}
		else
		{
			testAxis[axisTest] = false; // There is no collision along this axis
			return false;

		}

	}
	return true;

}

bool System::Physics::CheckShereSphereCollision(std::shared_ptr<Entity> sphere1, std::shared_ptr<Entity> sphere2)
{

	//setup data for the Sphere's
	auto sph1 = sphere1->get<Sphere>();
	auto sph2 = sphere2->get<Sphere>();

	auto t1 = sphere1->get<Component::Transformable>();
	auto t2 = sphere2->get<Component::Transformable>();

	//find the dist between the centre of each sphere
	glm::vec3 Dist = sph1->m_vCenter - sph2->m_vCenter;
	
	//find the magnitude of this distance
	float magDist = sqrt((Dist.x * Dist.x) + (Dist.y * Dist.y) + (Dist.z * Dist.z));
	
	//subtract the radius 
	magDist = magDist - sph1->m_fRadius;
	
	if (magDist <= sph2->m_fRadius)return true;
	else  return false;

}

bool System::Physics::CheckOBBSphereCollision(std::shared_ptr<Entity> eBox, std::shared_ptr<Entity> eSphere)
{
	//setup data for sphere and box
	auto sphere = eSphere->get<Sphere>();
	auto box = eBox->get<OBB>();

	auto tSphere = eSphere->get<Component::Transformable>();
	auto tBox = eBox->get<Component::Transformable>();
	
	//local version
	Sphere localSphere = *sphere;
	Component::Transformable localTransSphere = *tSphere;
	
	bool bExtremeClamp = true;


	//translate sphere by inverse box position
	localSphere.m_vCenter = localSphere.m_vCenter - box->m_vCenter;

	//rotate sphere by inverse box rotation
	localSphere.m_Rotation = glm::rotate(localSphere.m_Rotation, -tBox->getRotation().x, glm::vec3(1.0f, 0.0, 0.0f));
	localSphere.m_Rotation = glm::rotate(localSphere.m_Rotation, -tBox->getRotation().y, glm::vec3(0.0f, 1.0, 0.0f));
	localSphere.m_Rotation = glm::rotate(localSphere.m_Rotation, -tBox->getRotation().z, glm::vec3(0.0f, 0.0, 1.0f));

	localSphere.m_vCenter = localSphere.m_vCenter * mat3(localSphere.m_Rotation);

	//find the distance from center to center
	glm::vec3 overAllDistance =  glm::vec3(0,0,0) + localSphere.m_vCenter ;
	glm::vec3 clamp;


	//find which portion of space around the cube the sphere exists in
	
	if (overAllDistance.x < 0) // to the left of cube
	{
		if ((localSphere.m_vCenter.y < box->m_vDimensions.y / 2.0f && localSphere.m_vCenter.y > -box->m_vDimensions.y / 2.0f) && (localSphere.m_vCenter.z < box->m_vDimensions.z / 2.0f && localSphere.m_vCenter.z > -box->m_vDimensions.z / 2.0f))
		{
			std::cout << "left" << std::endl;
			clamp.x = -box->m_vDimensions.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = localSphere.m_vCenter.z;
			bExtremeClamp = false;
		}

	}

	if (overAllDistance.x > 0) // to the right of cube
	{
		if ((localSphere.m_vCenter.y < box->m_vDimensions.y / 2.0f && localSphere.m_vCenter.y > -box->m_vDimensions.y / 2.0f) && (localSphere.m_vCenter.z < box->m_vDimensions.z / 2.0f && localSphere.m_vCenter.z > -box->m_vDimensions.z / 2.0f))
		{
			std::cout << "right" << std::endl;
			clamp.x = box->m_vDimensions.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = localSphere.m_vCenter.z;
			bExtremeClamp = false;
		}

	}

	if (overAllDistance.y > 0) // above the cube
	{
		if ((localSphere.m_vCenter.x < box->m_vDimensions.x / 2.0f && localSphere.m_vCenter.x > -box->m_vDimensions.x / 2.0f) && (localSphere.m_vCenter.z < box->m_vDimensions.z / 2.0f && localSphere.m_vCenter.z > -box->m_vDimensions.z / 2.0f))
		{
			std::cout << "above" << std::endl;
			clamp.x = localSphere.m_vCenter.x;
			clamp.y = box->m_vDimensions.y / 2.0f;
			clamp.z = localSphere.m_vCenter.z;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.y < 0) // below the cube
	{
		if ((localSphere.m_vCenter.x < box->m_vDimensions.x / 2.0f && localSphere.m_vCenter.x > -box->m_vDimensions.x / 2.0f) && (localSphere.m_vCenter.z < box->m_vDimensions.z / 2.0f && localSphere.m_vCenter.z > -box->m_vDimensions.z / 2.0f))
		{
			std::cout << "below" << std::endl;
			clamp.x = localSphere.m_vCenter.x;
			clamp.y = -box->m_vDimensions.y / 2.0f;
			clamp.z = localSphere.m_vCenter.z;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z > 0) // infront of the cube
	{
		if ((localSphere.m_vCenter.x < box->m_vDimensions.x / 2.0f && localSphere.m_vCenter.x > -box->m_vDimensions.x / 2.0f) && (localSphere.m_vCenter.y < box->m_vDimensions.y / 2.0f && localSphere.m_vCenter.y > -box->m_vDimensions.y / 2.0f))
		{
			std::cout << "infront" << std::endl;
			clamp.x = localSphere.m_vCenter.x;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = box->m_vDimensions.z / 2.0f;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z < 0) // behind the cube
	{
		if ((localSphere.m_vCenter.x < box->m_vDimensions.x / 2.0f && localSphere.m_vCenter.x > -box->m_vDimensions.x / 2.0f) && (localSphere.m_vCenter.y < box->m_vDimensions.y / 2.0f && localSphere.m_vCenter.y > -box->m_vDimensions.y / 2.0f))
		{
			std::cout << "behind  " << std::endl;
			clamp.x = localSphere.m_vCenter.x;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = -box->m_vDimensions.z / 2.0f;
			bExtremeClamp = false;
		}

	}

	if (overAllDistance.z < 0 && overAllDistance.x < 0) // behind and left 
	{

		if (localSphere.m_vCenter.y < box->m_vDimensions.y / 2.0f && localSphere.m_vCenter.y > -box->m_vDimensions.y / 2.0)
		{
			std::cout << "behind and left " << std::endl;
			clamp.x = -box->m_vDimensions.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = -box->m_vDimensions.z / 2.0f;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z < 0 && overAllDistance.x > 0) // behind and right 
	{
		if (localSphere.m_vCenter.y < box->m_vDimensions.y / 2.0f && localSphere.m_vCenter.y > -box->m_vDimensions.y / 2.0f)
		{
			std::cout << "behind and right " << std::endl;
			clamp.x = box->m_vDimensions.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = -box->m_vDimensions.z / 2.0f;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z > 0 && overAllDistance.x > 0) // infront and right 
	{
		if (localSphere.m_vCenter.y < box->m_vDimensions.y / 2.0f && localSphere.m_vCenter.y > -box->m_vDimensions.y / 2.0f)
		{
			std::cout << "infront and right " << std::endl;
			clamp.x = box->m_vDimensions.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = box->m_vDimensions.z / 2.0f;
			bExtremeClamp = false;
		}

	}
	if (overAllDistance.z > 0 && overAllDistance.x < 0) // infront and left 
	{
		if (localSphere.m_vCenter.y < box->m_vDimensions.y / 2.0f && localSphere.m_vCenter.y > -box->m_vDimensions.y / 2.0f)
		{
			std::cout << "infront and left " << std::endl;
			clamp.x = -box->m_vDimensions.x / 2.0f;
			clamp.y = localSphere.m_vCenter.y;
			clamp.z = box->m_vDimensions.z / 2.0f;
			bExtremeClamp = false;
		}

	}


	//extreme clamps
	if (bExtremeClamp)
	{
		if (overAllDistance.x < 0) clamp.x = 0 - (box->m_vDimensions.x / 2.0f);
		if (overAllDistance.x >= 0) clamp.x = 0 + (box->m_vDimensions.x / 2.0f);
		if (overAllDistance.y < 0) clamp.y = 0 - (box->m_vDimensions.y / 2.0f);
		if (overAllDistance.y >= 0) clamp.y = 0 + (box->m_vDimensions.y / 2.0f);
		if (overAllDistance.z < 0) clamp.z = 0 - (box->m_vDimensions.z / 2.0f);
		if (overAllDistance.z >= 0) clamp.z = 0 + (box->m_vDimensions.z / 2.0f);
	}




	//find dist from clamp to center of circle
	glm::vec3 dist = clamp - localSphere.m_vCenter;
	float fDist = abs(sqrt((dist.x * dist.x) + (dist.y * dist.y) + (dist.z * dist.z)));
	//subract the radius
	fDist = fDist - localSphere.m_fRadius;

	//std::cout << "Overall : " << overAllDistance.x << " " << overAllDistance.y << " " << overAllDistance.z << std::endl;
	//std::cout << "Clamp : " << clamp.x << " " << clamp.y << " " << clamp.z << std::endl;

	if (fDist <= 0)
	{
		std::cout << "Collision" << endl;
		return true;
	}
	else
	{
		std::cout << "NO Collision" << endl;
		return false;
	}





	
}

void System::Physics::updateOBB(std::shared_ptr<Entity> eBox)
{

	auto box = eBox->get<OBB>();
	auto tBox = eBox->get<Component::Transformable>();

	box->m_Rotation = glm::rotate(box->m_Rotation, tBox->m_vRotation.x, glm::vec3(1.0f, 0.0, 0.0f));
	box->m_Rotation = glm::rotate(box->m_Rotation, tBox->m_vRotation.y, glm::vec3(0.0f, 1.0, 0.0f));
	box->m_Rotation = glm::rotate(box->m_Rotation, tBox->m_vRotation.z, glm::vec3(0.0f, 0.0, 1.0f));

	box->m_vCenter = glm::mat3(box->m_Rotation) * (tBox->m_vPosition + (box->m_vDimensions / 2.0f));


}


