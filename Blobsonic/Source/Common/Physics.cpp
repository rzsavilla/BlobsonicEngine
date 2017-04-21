#include "stdafx.h"
#include "Physics.h"
#include "AABB.h"
#include "OBB.h"


System::Physics::Physics()
{

}

void System::Physics::process(std::vector<std::shared_ptr<Entity>>* entities)
{
	m_vAABBS.clear();
	m_vOBBS.clear();

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
		for (int x = 0; x < m_vOBBS.size(); x++)
		{
			if (i != x)
			{
				CheckOBBOBBCollision(m_vOBBS.at(i), m_vOBBS.at(x));
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
	obox1->m_obbLocalPoints[0] = glm::vec3(box1->m_vCenter.x - box1->m_vScale.x / 2, box1->m_vCenter.y + box1->m_vScale.y / 2, box1->m_vCenter.z + box1->m_vScale.z / 2);	//Front - Top left
	obox1->m_obbLocalPoints[1] = glm::vec3(box1->m_vCenter.x + box1->m_vScale.x / 2, box1->m_vCenter.y + box1->m_vScale.y / 2, box1->m_vCenter.z + box1->m_vScale.z / 2);	//Front - Top Right
	obox1->m_obbLocalPoints[2] = glm::vec3(box1->m_vCenter.x + box1->m_vScale.x / 2, box1->m_vCenter.y - box1->m_vScale.y / 2, box1->m_vCenter.z + box1->m_vScale.z / 2);	//Front - Bottom Right
	obox1->m_obbLocalPoints[3] = glm::vec3(box1->m_vCenter.x - box1->m_vScale.x / 2, box1->m_vCenter.y - box1->m_vScale.y / 2, box1->m_vCenter.z + box1->m_vScale.z / 2);	//Front - Bottom left
	obox1->m_obbLocalPoints[4] = glm::vec3(box1->m_vCenter.x - box1->m_vScale.x / 2, box1->m_vCenter.y + box1->m_vScale.y / 2, box1->m_vCenter.z - box1->m_vScale.z / 2);	//Back - Top left
	obox1->m_obbLocalPoints[5] = glm::vec3(box1->m_vCenter.x + box1->m_vScale.x / 2, box1->m_vCenter.y + box1->m_vScale.y / 2, box1->m_vCenter.z - box1->m_vScale.z / 2);	//Back - Top Right
	obox1->m_obbLocalPoints[6] = glm::vec3(box1->m_vCenter.x + box1->m_vScale.x / 2, box1->m_vCenter.y - box1->m_vScale.y / 2, box1->m_vCenter.z - box1->m_vScale.z / 2);	//Back - Bottom Right
	obox1->m_obbLocalPoints[7] = glm::vec3(box1->m_vCenter.x - box1->m_vScale.x / 2, box1->m_vCenter.y - box1->m_vScale.y / 2, box1->m_vCenter.z - box1->m_vScale.z / 2);	//Back - Bottom left


	obox2->m_obbLocalPoints[0] = glm::vec3(box2->m_vCenter.x - box2->m_vScale.x / 2, box2->m_vCenter.y + box2->m_vScale.y / 2, box2->m_vCenter.z + box2->m_vScale.z / 2);	//Front - Top left
	obox2->m_obbLocalPoints[1] = glm::vec3(box2->m_vCenter.x + box2->m_vScale.x / 2, box2->m_vCenter.y + box2->m_vScale.y / 2, box2->m_vCenter.z + box2->m_vScale.z / 2);	//Front - Top Right
	obox2->m_obbLocalPoints[2] = glm::vec3(box2->m_vCenter.x + box2->m_vScale.x / 2, box2->m_vCenter.y - box2->m_vScale.y / 2, box2->m_vCenter.z + box2->m_vScale.z / 2);	//Front - Bottom Right
	obox2->m_obbLocalPoints[3] = glm::vec3(box2->m_vCenter.x - box2->m_vScale.x / 2, box2->m_vCenter.y - box2->m_vScale.y / 2, box2->m_vCenter.z + box2->m_vScale.z / 2);	//Front - Bottom left
	obox2->m_obbLocalPoints[4] = glm::vec3(box2->m_vCenter.x - box2->m_vScale.x / 2, box2->m_vCenter.y + box2->m_vScale.y / 2, box2->m_vCenter.z - box2->m_vScale.z / 2);	//Back - Top left
	obox2->m_obbLocalPoints[5] = glm::vec3(box2->m_vCenter.x + box2->m_vScale.x / 2, box2->m_vCenter.y + box2->m_vScale.y / 2, box2->m_vCenter.z - box2->m_vScale.z / 2);	//Back - Top Right
	obox2->m_obbLocalPoints[6] = glm::vec3(box2->m_vCenter.x + box2->m_vScale.x / 2, box2->m_vCenter.y - box2->m_vScale.y / 2, box2->m_vCenter.z - box2->m_vScale.z / 2);	//Back - Bottom Right
	obox2->m_obbLocalPoints[7] = glm::vec3(box2->m_vCenter.x - box2->m_vScale.x / 2, box2->m_vCenter.y - box2->m_vScale.y / 2, box2->m_vCenter.z - box2->m_vScale.z / 2);	//Back - Bottom left

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
			std::cout << "No" << std::endl;
			return false;

		}

	}
	std::cout << "Collision" << std::endl;
	return true;

}
