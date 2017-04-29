/*
*	@class Entity
*	@brief Container for components
*/

#pragma once

#include <map>
#include <memory>
#include <typeindex>

#include "Destroyable.h"
#include "UniqueID.h"

#include "Component.h"

static void LuaLoaded() {
	std::cout << "Lua is working\n";
}

class Entity: public Destroyable, public UniqueID, public std::enable_shared_from_this<Entity> {
private:
	std::map<std::type_index, std::shared_ptr<void>> m_components;
	int m_iUID;	//!< Unique ID

	const bool m_bDebug = true;	//!< Flag for Couts
public:
	Entity() {
		this->setUID();
		if (m_bDebug) std::cout << "Entity Created: " << this->getUID() << "\n";
		//--DELETE-- Old code replaced by UniqueID class
		//m_iUID = iUniqueIDCounter;	//Set Unique ID
		//iUniqueIDCounter++;
	}
	
	~Entity() { 
		m_components.clear();	//Remove all attached components
	}

	template<typename T, typename... Args>
	T &attach(Args &&...args) {
		m_components[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
		
		std::shared_ptr<Component::Component> component;
		component = std::static_pointer_cast<Component::Component>(m_components[typeid(T)]);
		component->setParent(shared_from_this());
		return *get<T>();
	}

	template<typename T>
	bool has() {
		return m_components.find(typeid(T)) != m_components.end();
	}

	template<typename T>
	T *get() {
		if (has<T>()) {
			return std::static_pointer_cast<T>(m_components[typeid(T)]).get();
		}
		else {
			terminate();
		}
	}

	template<typename T>
	int getComponentByID(const int id) {
		std::cout << "Component Retrieved: " << id << "\n";

		return 0;
	}

	template<typename T>
	void removeComponent() {
		m_components.erase(typeid(T));
	}

	//! Return Unique Identifier
	int getID() {
		return m_iUID;
	}
};