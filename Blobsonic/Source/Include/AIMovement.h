#pragma once

#include "Component.h"

namespace Component {
	class AIMovement : public Component{
	private:

	public:
		AIMovement();

		//!Set the variables of a by reading the values set within a lua table
		void setComponent(luabridge::LuaRef& table) {};
	};

}