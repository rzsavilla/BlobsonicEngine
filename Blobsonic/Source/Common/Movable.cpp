#include <stdafx.h>
#include "..\Include\Movable.h"

OC::Movable::Movable()
{

}

void OC::Movable::handleMessage(std::shared_ptr<Message> msg)
{
	if (msg->sID == "Movable_SetVel") {
		m_vVelocity = static_cast<M_Movable::SetVel*>(msg.get())->newVelocity;	//get data from message
	}
}

void OC::Movable::update(float dt)
{
	std::cout << "Velocity: " << m_vVelocity.x << " " << m_vVelocity.y << " " << m_vVelocity.z << "\n";
}
