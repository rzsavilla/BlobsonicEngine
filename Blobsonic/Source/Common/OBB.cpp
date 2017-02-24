#include <stdafx.h>
#include "OBB.h"
#include <iostream>


OBB::OBB()
{
	
}

OBB::OBB(Model model)
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

void OBB::update(const float dt)
{

	
	
	m_RenderModel.setPosition(m_vPosition);

}

void OBB::init()
{
}

void OBB::handleMessage(std::shared_ptr<Message> msg)
{
}

void OBB::setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr)
{
}

void OBB::CollideWithBox(OBB* other)
{


	//setup data for the OBB's
	m_vCenter = m_vPosition + m_vScale / 2.0f;
	other->m_vCenter = other->m_vPosition + other->m_vScale / 2.0f;
	
	// begin collison check!!!!

	//create local versions

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

	//multiply points by rotation matrix
	obb1LocalPoints[0] = m_rotationMatrix  * obb1LocalPoints[0];
	obb1LocalPoints[1] = m_rotationMatrix  * obb1LocalPoints[1];
	obb1LocalPoints[2] = m_rotationMatrix  * obb1LocalPoints[2];
	obb1LocalPoints[3] = m_rotationMatrix  * obb1LocalPoints[3];
	obb1LocalPoints[4] = m_rotationMatrix  * obb1LocalPoints[4];
	obb1LocalPoints[5] = m_rotationMatrix  * obb1LocalPoints[5];
	obb1LocalPoints[6] = m_rotationMatrix  * obb1LocalPoints[6];
	obb1LocalPoints[7] = m_rotationMatrix  * obb1LocalPoints[7];

	//multiply points by rotation matrix
	obb2LocalPoints[0] = obb2LocalPoints[0] * other->m_rotationMatrix;
	obb2LocalPoints[1] = obb2LocalPoints[1] * other->m_rotationMatrix;
	obb2LocalPoints[2] = obb2LocalPoints[2] * other->m_rotationMatrix;
	obb2LocalPoints[3] = obb2LocalPoints[3] * other->m_rotationMatrix;
	obb2LocalPoints[4] = obb2LocalPoints[4] * other->m_rotationMatrix;
	obb2LocalPoints[5] = obb2LocalPoints[5] * other->m_rotationMatrix;
	obb2LocalPoints[6] = obb2LocalPoints[6] * other->m_rotationMatrix;
	obb2LocalPoints[7] = obb2LocalPoints[7] * other->m_rotationMatrix;

	//create normals for each face
	obb1Normals[0] = m_rotationMatrix * glm::vec3(0, 0, 1)  ;  // front face
	obb1Normals[1] = m_rotationMatrix * glm::vec3(0, 0, -1) ; // back face
	obb1Normals[2] = m_rotationMatrix * glm::vec3(-1, 0, 0) ; // left face
	obb1Normals[3] = m_rotationMatrix * glm::vec3(1, 0, 0)  ; // right face
	obb1Normals[4] = m_rotationMatrix * glm::vec3(0, 1, 0)  ; // Top face
	obb1Normals[5] = m_rotationMatrix * glm::vec3(0, -1, 0) ; // bottom face
						
	obb2Normals[0] = other->m_rotationMatrix * glm::vec3(0, 0, 1);  // front face
	obb2Normals[1] = other->m_rotationMatrix * glm::vec3(0, 0, -1); // back face
	obb2Normals[2] = other->m_rotationMatrix * glm::vec3(-1, 0, 0); // left face
	obb2Normals[3] = other->m_rotationMatrix * glm::vec3(1, 0, 0); // right face
	obb2Normals[4] = other->m_rotationMatrix * glm::vec3(0, 1, 0); // Top face
	obb2Normals[5] = other->m_rotationMatrix * glm::vec3(0, -1, 0); // bottom face
		
		

	//project 3 axis 
	for (int axisTest = 0; axisTest < 6; axisTest++)
	{
		//values for min other->and max
		float obb1Min = 999999999999999999999.0f;
		float obb1Max = -999999999999999999999.0f;
		float obb2Min = 999999999999999999999.0f;
		float obb2Max = -999999999999999999999.0f;

			
		// check all vertecies on box 1
		for (int box1Vertex = 0; box1Vertex < 8; box1Vertex++)
		{
			float fDotProduct = glm::dot(obb1Normals[axisTest], obb1LocalPoints[box1Vertex]);
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
			float fDotProduct = glm::dot(obb1Normals[axisTest], obb2LocalPoints[box2Vertex]);
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
			testAxis[axisTest] = false; // There is a collision along this axis
			std::cout << "NO Collision" << std::endl;
			return;
				
		}

	}

	std::cout << "Collision" << std::endl;

	

}

void OBB::movementForTesting(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

