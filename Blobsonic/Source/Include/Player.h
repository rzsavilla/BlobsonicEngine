#pragma once

#pragma once

#include <stdafx.h>
#include "Component.h"

namespace Component {
	struct Player : public Component {
		Player() {}
		float m_fMoveSpeed = 10;

		//!Set the variables of a by reading the values set within a lua table
		void setComponent(luabridge::LuaRef& table) {};
	};
}