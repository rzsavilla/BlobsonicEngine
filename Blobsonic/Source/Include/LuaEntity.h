/*
*	@class LuaEntity
*	@brief Interface class for creating entities
*	@author Rozen Savilla
*	Stores variables and functions
*/

#pragma once

#include "MessageHandler.h"

#include "Entity.h"

class LuaEntity {
private:
	std::shared_ptr<Entity> m_entity;
	bool m_bDebug = true;
public:
	LuaEntity();	//!< Default Constructor
	
	void attachComponent(const std::string& sComponent);

	unsigned int getID();
};