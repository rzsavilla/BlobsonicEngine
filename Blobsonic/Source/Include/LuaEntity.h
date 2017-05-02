/*
*	@class LuaEntity
*	@brief Handle for a C++ Entity
*	@author Rozen Savilla
*	Stores variables and functions
*/

#pragma once

#include "MessageHandler.h"

#include "Entity.h"

#include "sol.hpp"

struct LuaEntity {
	std::shared_ptr<Entity> m_entity;
	bool m_bDebug = true;

	LuaEntity();	//!< Default Constructor
	
	void attachComponent(const std::string& sComponent);

	unsigned int getID();

	void lua_get(sol::table t);
};