#include <stdafx.h>
#include "Actor.h"

Actor::Actor()
{
	attachComponent(std::make_unique<OC::Movable>());
}

void Actor::update(float dy)
{
	sendLocalMessage(std::make_shared<M_Movable::SetVel>(glm::vec3(0.0f, 1.0f, 2.0f)));
}
