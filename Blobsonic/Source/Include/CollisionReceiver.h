/**
* @class	CollisionReceiver
* @brief	Abstract class for receiving collision messages
* Class inherits this in order to be notified of collision messages
*/

#pragma once

#include "stdafx.h"
#include "Message.h"
#include "Entity.h"
#include "UniqueID.h"

class CollisionReceiver :public UniqueID {
public:
	CollisionReceiver() { setUID(); }
	virtual void registerCollision(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) = 0;
};