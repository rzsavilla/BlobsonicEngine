/*
*	@struct Component
*	@brief Abstract class for components simply holds data
*/

#pragma once
#include "stdafx.h"
#include "UniqueID.h"

#include "Entity.h"
#include "Name.h"

#include "LuaBridge.h"

namespace Component {
	struct Component: public UniqueID, public Name {
	private:
		std::shared_ptr<Entity> m_parent;
	public:
		Component() {
			setUID();
			m_parent = NULL;
		}

		void setParent(std::shared_ptr<Entity> parent) {
			m_parent = parent;
		}
		
		bool hasParent() {
			return (m_parent != NULL);
		}
		const std::shared_ptr<Entity> getParent() const {
			return m_parent;
		}

		//!Set the variables of a by reading the values set within a lua table
		virtual void setComponent(luabridge::LuaRef& table) = 0;
	};
}