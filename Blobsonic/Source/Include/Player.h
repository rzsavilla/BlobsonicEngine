#pragma once

#pragma once

#include <stdafx.h>
#include "Component.h"

namespace Component {
	class Player : public Component {
	private:
		float m_fMoveSpeed;
		float m_fTurnSpeed;
	public:
		Player();	//!< Constructor
		void setMoveSpeed(float newSpeed);		//!< Set value for movement speed
		void setTurnSpeed(float newTurnSpeed);	//!< Set value for turning speed

		float getMoveSpeed();
		float getTurnSpeed();
	};
}