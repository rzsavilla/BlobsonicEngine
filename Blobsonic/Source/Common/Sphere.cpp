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

void Sphere::movementForTesting(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

