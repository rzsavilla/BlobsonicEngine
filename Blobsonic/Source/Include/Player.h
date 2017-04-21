#pragma once

#pragma once

#include <stdafx.h>
#include "Component.h"

namespace Component {
	struct Player : public Component {
		Player() {}
		float m_fMoveSpeed = 10;
	};
}