/*
*	@struct Component
*	@brief Abstract class for components simply holds data
*/

#pragma once
#include "Entity.h"

namespace Component {
	struct Component {
	private:
		std::shared_ptr<Entity> m_parent;
	public:
		void setParent(std::shared_ptr<Entity> parent) {
			if (!hasParent()) m_parent = parent;
		}
		
		bool hasParent() {
			return (m_parent != NULL);
		}
		std::shared_ptr<Entity> getParent() {
			return m_parent;
		}
	};
}