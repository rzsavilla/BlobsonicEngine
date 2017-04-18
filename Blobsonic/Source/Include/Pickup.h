#pragma once

#include "Component.h"

namespace Component {
	class Pickup : public Component {
	private:
		bool m_bCollected = false;	//!< Current Pickup State
	public:
		bool bIsCollected();	//!< Returns boolean m_bCollected
	};
}