#include <stdafx.h>
#include "Capsule.h"
#include <iostream>


Capsule::Capsule()
{

}

Capsule::Capsule(Model model)
{
	m_RenderModel = model;
	//initliaise variables
	m_vPosition = m_RenderModel.getPosition();
	m_vScale = m_RenderModel.getScale();
	m_vCenter = m_vPosition + m_vScale / 2.0f;


}

void Capsule::update(const float dt)
{
	m_RenderModel.setPosition(m_vPosition);
}

void Capsule::init()
{
}

void Capsule::handleMessage(std::shared_ptr<Message> msg)
{
}

void Capsule::setLocalMsgPtr(std::vector<std::shared_ptr<Message>>* ptr)
{
}

void Capsule::CollideWithCapsule(Capsule* other)
{



}

void Capsule::movementForTesting(float x, float y, float z)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	m_vPosition.z += z;
}

