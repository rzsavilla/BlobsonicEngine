#include <stdafx.h>
#include "BoxPhysics.h"
#include <iostream>


BoxPhysics::BoxPhysics()
{
	
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
	
	if (magEarlyDist > roughSize * 5.0f) // if further than 10 times the rouch size of the box away
	{
		std::cout << "Early out" << std::endl;
		return; // escape collision test before any intensive testing begins
	}
	else
	{
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
		
		//values for min other->and max
		float obb1Min = 999999999999999999999.0f;
		float obb1Max = -999999999999999999999.0f;
		float obb2Min = 999999999999999999999.0f;
		float obb2Max = -999999999999999999999.0f;


		//project 3 axis 
		for (int axisTest = 0; axisTest < 3; axisTest++)
		{
			
			// check all vertecies on box 1
			for (int box1Vertex = 0; box1Vertex < 8; box1Vertex++)
			{
				float fDotProduct = glm::dot(obb1Normals[axisTest*2], obb1LocalPoints[box1Vertex]);
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
				float fDotProduct = glm::dot(obb1Normals[axisTest*2], obb2LocalPoints[box2Vertex]);
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

			std::cout << obb1Min << std::endl;
			std::cout << obb1Max << std::endl;
			std::cout << obb2Min << std::endl;
			std::cout << obb2Max << std::endl;
			std::cout << testAxis[axisTest] << " : " << axisTest << std::endl;

		}

		std::cout << "Collision" << std::endl;

	}

}

void BoxPhysics::movementForTesting(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

