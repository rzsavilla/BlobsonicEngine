#include <stdafx.h>
#include "Actor.h"

Actor::Actor()
{
	attachComponent(std::make_unique<OC::Movable>());
}
