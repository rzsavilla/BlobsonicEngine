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
			m_parent = parent;
		}
		
		bool hasParent() {
			return (m_parent != NULL);
		}
		const std::shared_ptr<Entity> getParent() const {
			return m_parent;
		}
	};
}