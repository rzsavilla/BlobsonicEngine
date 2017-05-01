/*
*	@file AIPerception.h
*	@class AIPerception
*	@brief Allows entity to sense other entities 
*	@author Rozen Savilla
*	System takes control of entities with AI components and applies their behaviour
*/

#pragma once

#include "Component.h"

namespace Component {
	class AIPerception {
	private:

	public:

		//!Set the variables of a by reading the values set within a lua table
		void setComponent(luabridge::LuaRef& table) {};
	};
};